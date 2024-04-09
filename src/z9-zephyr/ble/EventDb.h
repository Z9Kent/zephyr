/*
 * Events are stored in a pair of circular buffers: one for priority events and one for normal events.
 * The zephyr facility: File-Circular-Buffers is used to facilitate the storage
 * 
 * Provide a single "store event" interface which examines the Event to determine the file
*/

#pragma once

//#include "Z9LockIOProtocol_Current.h"

#include <zephyr/device.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/fs/fcb.h>
#include <string.h>
#include <cstdint>
#include <functional>
#include <utility>
#include <time.h>

// macro to create EVENT
// Events codes in Z9LockIO protocol definition
#include "Z9LockIOProtocol_Current.h"

// TODO: add args to set flags other than true
#define  EVT(code, MODS...)  LockEvt{ .evtCode=code }
#define PEVT(code, MODS...)  LockEvt{ .evtCode=code, {.priority=true}}


// Declare the FileSystem Names
#define FS_NORMAL       event_normal
#define FS_PRIORITY     event_priority

namespace z9{}
using namespace z9;

// Declare Data-type stored in the Event Circular buffer
struct LockEventFsItem
{
    // to be written: set time, possibly add header
    LockEventFsItem(LockEvt const& evt, uint8_t id, const void *content, uint16_t contentLength);

    // convert retrieved item to object
    LockEventFsItem(uint8_t *data, uint16_t bytesRead);

    // get pointer + count for write
    uint16_t getRaw(uint8_t *data, uint16_t max) const;

    bool isDeleted() const { return evt.evtCode == 0; }
    void serialize(std::function<void(uint8_t)> const& writer) const;

    // utilities
    bool priority() const { return evt.modifiers.priority; }
    auto evtCode () const { return evt.evtCode;            }
    
    enum class EventCompare { Before, Equal, After }; 
    EventCompare test(LockEvtIdentifierRange const& id) const;

    bool matches(LockEvtIdentifier const& id) const;
    void doDelete(fcb_entry_ctx *loc_ctx);
//private:
    LockEvt evt;
    uint8_t id;
    const void *content;
    uint16_t contentLength;

};

// Declare the File System
struct LockEventFs
{
    // XXX doClear should be false for production
    LockEventFs(int fixed_area_id, std::size_t sizeBytes, bool doClear = true)
    {
        uint32_t cnt = sizeBytes / 4096;
        auto p  = new flash_sector[sizeBytes/4096];
        auto rc = flash_area_get_sectors(fixed_area_id, &cnt, p);
        file.f_sector_cnt = cnt;
        file.f_sectors    = p;
        if (rc < 0)
            printk("%s: flash_area_get_sectors failed: %d\n", __func__, rc);
        else if ((rc = fcb_init(fixed_area_id, &file)))
        {
            printk("%s: fcb_init failed: %d\n", __func__, rc);
            const flash_area *fa_p;
            rc = flash_area_open(fixed_area_id, &fa_p);
            flash_area_erase(fa_p, 0, fa_p->fa_size);   // erase everything...
            printk("%s: flash_area erased\n", __func__);
            rc = fcb_init(fixed_area_id, &file);        // and retry...
        }
        else
            printk("%s: fcb_init complete\n", __func__);

        if (doClear)
            fcb_clear(&file);
    }

    LockEventFs() {}

    // put item in FS directly
    void write(LockEventFsItem const& evt);

    // walk thru FCB items to report or select for delete
    int walk(fcb_walk_cb cb, void *cb_arg = {}, flash_sector *sector = {})
    {
        return fcb_walk(&file, sector, cb, cb_arg);
    }

    // recycle oldest sector
    void rotate() { fcb_rotate(&file); }

    bool isEmpty() { return !hasEvents; }
    bool hasData(bool state);
    
private:
    fcb file {};
    bool hasEvents {true};
};

// Declare the Event Database interface class
struct LockEventDb 
{
    // allow content to be passed as "type"
    template <typename T = LockEvtContent_None>
    void save(LockEvt const& evt, T const& content = {}) const
    {
        return save(evt, T::DISCRIMINATOR, static_cast<const void *>(&content), sizeof(T));
    }

    // Z9LockIO Protocol support
    void consume(bool priority, LockEvtIdentifier const& from, LockEvtIdentifier const& to) const;
    uint8_t extract(bool priority, uint8_t max, std::function<void(uint8_t)> const& writer) const;

    void dump() const;

    // test if event buffers(s) are empty
    bool isEmpty() const { return getFs(false).isEmpty() && getFs(true).isEmpty(); }

    static auto& instance()
    {
        static LockEventDb _;
        return _;
    }

private:
    // TODO: errors (or let Throw handle it)
    // save an event. length is of variable content only
    // NB: event times are overwritten to ensure asending order
    void save(LockEvt const& evt, uint8_t id, const void *content_p, uint16_t contentLength) const;

    // NB: put `LockEventFs` in static methods so that ctors will not run at startup
    // NB: local static's are initialized first time control passes thru
    static auto& priorityFs()
    {
        static LockEventFs fs(FIXED_PARTITION_ID(event_priority_partition),
                              FIXED_PARTITION_SIZE(event_priority_partition));
        return fs;
    }
    static auto& normalFs()
    {
        static LockEventFs fs(FIXED_PARTITION_ID(event_normal_partition),
                              FIXED_PARTITION_SIZE(event_normal_partition));
        return fs;
    }
    LockEventFs& getFs(bool priority) const
    {
        return priority ? priorityFs() : normalFs();
    }
};

