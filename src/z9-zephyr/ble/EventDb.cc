/*
 * Events are stored in a pair of circular buffers: one for priority events and one for normal events.
 * The zephyr facility: File-Circular-Buffers is used to facilitate the storage
 * 
 * Provide a single "store event" interface which examines the Event to determine the file
*/


#include "EventDb.h"
#include "Z9Serialize.h"
#include <zephyr/kernel.h>

using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;


void LockEventDb::save(LockEvt const& evt, uint8_t id, const void *content_p, uint16_t contentLength) const
{
    getFs(evt.modifiers.priority).write({evt, id, content_p, contentLength});
}

void LockEventDb::dump() const
{
    auto dump_cb = [](fcb_entry_ctx *loc_ctx, void *arg)
    {
        auto count_p = static_cast<unsigned *>(arg);

        auto n = loc_ctx->loc.fe_data_len;
        uint8_t buf[n], *p = buf;

        printk("%s: reading %d bytes at: sector=%p, data_offset=%u\n",
                    __func__, n, loc_ctx->loc.fe_sector, loc_ctx->loc.fe_data_off);
        auto rc = flash_area_read(loc_ctx->fap, FCB_ENTRY_FA_DATA_OFF(loc_ctx->loc), buf, n);
        if (rc < 0)
            printk("Error: result=%d\n", rc);
        else
        {
            printk("%3u: Event (%d bytes): ", ++(*count_p), n);
            while (n--) printk("%02x", *p++);
            printk("\n");
        }
        return 0;
    };

    // cb_arg is `unsigned`
    unsigned count{};

    printk("%s: Pending Priority Events:\n", __func__);   
    printk("%s: Pending Normal Events:\n", __func__);
    normalFs().walk(dump_cb, &count); 
    printk("%s: *** DONE ***\n", __func__);
}
    
uint8_t LockEventDb::extract(bool priority, uint8_t max_, std::function<void(uint8_t)> const& writer_) const
{
    // fcb_walk is `C`: bundle references into struct compatible with `fcb_walk`
    struct extract_arg
    {
        decltype(writer_)& writer;
        decltype(max_)   & max;
    } arg = { writer_, max_ };

    auto reader_cb = [](fcb_entry_ctx *loc_ctx, void *arg) -> int
    {
        static constexpr auto func = "reader_cb[]";
        auto arg_p = static_cast<extract_arg *>(arg);

        // read next entry
        auto n = loc_ctx->loc.fe_data_len;
        uint8_t buf[n];

        printk("%s: reading %d bytes at: sector=%p, data_offset=%u\n",
                    func, n, loc_ctx->loc.fe_sector, loc_ctx->loc.fe_data_off);
        flash_area_read(loc_ctx->fap, FCB_ENTRY_FA_DATA_OFF(loc_ctx->loc), buf, n);

        LockEventFsItem evt(buf, n);
        printk("%s: evt_code=%d, hms=%02d:%02d:%02d\n", func, evt.evt.evtCode, 
            evt.evt.dateTime.hour, evt.evt.dateTime.minute, evt.evt.dateTime.second);

        if (evt.isDeleted()) return 0;        // next
        evt.serialize(arg_p->writer);
        return !--arg_p->max;
    };

    auto allowed = arg.max;
    getFs(priority).walk(reader_cb, &arg);
    auto count = allowed - arg.max;
    //hasData(count);
    return count;
}
    
void LockEventDb::consume(bool priority, LockEvtIdentifier const& from_, LockEvtIdentifier const& to_) const
{
    // fcb_walk is `C`: bundle references to args for walker
    struct consume_arg
    {
        decltype(from_)& from;
        decltype(to_)&   to;
        bool             foundFrom{}; 
        bool             foundTo{};
        bool             isDeleting{};
    } arg = { from_, to_ };

    auto consume_cb = [](fcb_entry_ctx *loc_ctx, void *arg) -> int
    {
        auto arg_p = static_cast<consume_arg *>(arg);
        
        // read next entry
        auto n = loc_ctx->loc.fe_data_len;
        uint8_t buf[n];

        printk("%s: reading %d bytes at: sector=%p, data_offset=%u\n",
                    __func__, n, loc_ctx->loc.fe_sector, loc_ctx->loc.fe_data_off);
        flash_area_read(loc_ctx->fap, FCB_ENTRY_FA_DATA_OFF(loc_ctx->loc), buf, n);

        LockEventFsItem evt(buf, n);            // construct Evt from stored data

        printk("%s: evt_code=%d, hms=%02d:%02d:%02d\n", "consume_cb", evt.evt.evtCode, 
            evt.evt.dateTime.hour, evt.evt.dateTime.minute, evt.evt.dateTime.second);

        if (evt.isDeleted()) return 0;          // ignore deleted ones

        // look for `from` first
        if (!arg_p->foundFrom)
            arg_p->foundFrom = evt.matches(arg_p->from);
        if (!arg_p->foundTo)
            arg_p->foundTo = evt.matches(arg_p->to);

        // if in range & on delete pass, execute
        if (arg_p->foundFrom && arg_p->isDeleting)
        {
            evt.doDelete(loc_ctx);
            uint8_t buf_after[n];
        
            printk("%s: reading %d bytes at: sector=%p, data_offset=%u\n",
                    __func__, n, loc_ctx->loc.fe_sector, loc_ctx->loc.fe_data_off);
            flash_area_read(loc_ctx->fap, FCB_ENTRY_FA_DATA_OFF(loc_ctx->loc), buf_after, n);

            printk("%s: buf before: ", __func__);
            auto s = buf;
            for (auto i = 0; i++ < n; ) printk("%02x", *s++);
            printk("\n");
            printk("%s: buf after : ", __func__);
            s = buf_after;
            for (auto i = 0; i++ < n; ) printk("%02x", *s++);
            printk("\n");
        }    

        printk("%s: foundFrom=%d, foundTo=%d, deleting=%d\n", "consume_cb",
            arg_p->foundFrom, arg_p->foundTo, arg_p->isDeleting);
        return arg_p->foundTo;                  // loop if not done
    };

    // walk FCB looking for start & end
    // walk exits on `foundTo`
    if (getFs(priority).walk(consume_cb, &arg))
    {
        // both `To` and `From` present -- do delete on second pass
        if (arg.foundFrom)
        {
            arg.foundFrom = arg.foundTo = false;
            arg.isDeleting = true;
            getFs(priority).walk(consume_cb, &arg);

            // TODO: should walk oldest sector to rotate
        }
    }  
}

void LockEventFs::write(LockEventFsItem const& evt)
{
    // need to allocate area to write the data
    // NB: all `fsb` routines return NZ for error
    uint8_t buf[100];
    auto len = evt.getRaw(buf, sizeof(buf));
    struct fcb_entry loc;

    // XXX loop on error (ie full)
    fcb_append(&file, len, &loc);

    // write the data to flash via flash area API
    printk("%s: writing %d bytes at: sector=%p (%u), data_offset=%u, buf=%p\n",
            __func__, len, loc.fe_sector, loc.fe_sector - file.f_sectors, loc.fe_data_off, buf);
    flash_area_write(file.fap, FCB_ENTRY_FA_DATA_OFF(loc), buf, len);
    
    // write checksum to validate data
    fcb_append_finish(&file, &loc);
    //hasData(true);
}

// FCB entries must be multiple of 4 bytes. Pad as required
uint16_t LockEventFsItem::getRaw(uint8_t *buf, uint16_t max) const
{
    std::memcpy(buf, &evt, sizeof(evt));
    buf += sizeof(evt);
    *buf++ = id;
    std::memcpy(buf, content, contentLength);
    auto n = sizeof(evt) + 1 + contentLength;
    {
        printk("%s: fcb data (%u bytes): ", __func__, n);
        auto i = n;
        auto s = buf - sizeof(evt) - 1;
        while (i--)
            printk("%02x ", *s++);
        printk("\n");
    }
    return (n + 3) & ~3;
};

void LockEventFsItem::serialize(std::function<void(uint8_t)> const& writer) const
{
    auto proto = getFormatter<LockEvt>();
    proto->serialize(writer, (uint8_t *)(void *)&evt, 100, 100);
    writer(id);     // evt format discriminator
    if (id == LockEvtContent_CredUnid::DISCRIMINATOR)
    {
        LockEvtContent_CredUnid xtra;       // ensure alignment
        std::memcpy(&xtra, content, sizeof(xtra));
        getFormatter<LockEvtContent_CredUnid>()->serialize(writer, (uint8_t *)(void *)&xtra, 100, 100);   
    }
}


// Format Event (and EvtContent) for flash. Initialize time to now.
LockEventFsItem::LockEventFsItem(LockEvt const& evt, uint8_t id, const void *content, uint16_t contentLength) : 
        evt(evt), id(id), content(content),  contentLength(contentLength)
{
    auto uptime_msec  = k_uptime_get();
    time_t uptime_sec = uptime_msec / 1000;
    auto tm = gmtime(&uptime_sec);
    auto& dt  = this->evt.dateTime;
    dt.year   = tm->tm_year + 1900;
    dt.month  = tm->tm_mon  + 1;
    dt.day    = tm->tm_mday;
    dt.day    = tm->tm_mday;
    dt.hour   = tm->tm_hour;
    dt.minute = tm->tm_min;
    dt.second = tm->tm_sec;
}

// construct FsItem from raw data (undo getRaw)
LockEventFsItem::LockEventFsItem(uint8_t *data, uint16_t bytesRead)
{
    std::memcpy(&evt, data, sizeof(evt));
    data += sizeof(evt);
    id = *data++;
    content = data;
    contentLength = bytesRead - sizeof(evt) - 1;
}

bool LockEventFsItem::matches(LockEvtIdentifier const& id) const
{
    return evt.evtCode == id.evtCode && !std::memcmp(&evt.dateTime, &id.dateTime, sizeof(id.dateTime));
}

void LockEventFsItem::doDelete(fcb_entry_ctx *loc_ctx)
{
    // delete by marking `evtCode` as Zero
    evt.evtCode = {};

    // write to flash
    // data in buffer generated by `getRaw`, so match format
    // NB: minimum write is word, hence all the 3s (ie sizeof(word)-1)
    constexpr auto offset = offsetof(LockEvt, evtCode);
    constexpr auto begin  = offset &~ 3;       // word align
    constexpr auto end    = (offset + sizeof(evt.evtCode) + 3) &~ 3;
    constexpr uint8_t zero[end-begin] = {};

    printk("%s: offset=%d, begin=%d, end=%d, sizeof(zero)=%u\n", __func__,
        offset, begin, end, sizeof(zero));

    auto& loc = loc_ctx->loc;
    printk("%s: writing %d bytes at: sector=%p, data_offset=%u\n",
            __func__, sizeof(zero), loc.fe_sector, loc.fe_data_off + begin);
    auto rc = flash_area_write(loc_ctx->fap, FCB_ENTRY_FA_DATA_OFF(loc_ctx->loc) + begin, zero, sizeof(zero));
    if (rc)
        printk("%s: write error: %d\n", __func__, rc);
}