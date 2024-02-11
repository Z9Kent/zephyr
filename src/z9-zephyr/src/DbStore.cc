/*
error_t DbStore_deleteLockEvt_Async(struct DbStore *self, bool priority, const struct LockEvtIdentifierRange *range, RouteIndex returnRoute, uint8_t callerContext)

error_t DbStore_storeLockEvt_Async(struct DbStore *self, struct LockEvt *evt, RouteIndex returnRoute)
error_t DbStore_loadLockEvt_Async(struct DbStore *self, bool priority, KAB_Hdr *kab_LockEvt, uint16_t max, RouteIndex returnRoute, uint8_t callerContext)
*/
#if 0
   const static struct DbStore prototype = {
        .allPaths = {
            // ARGS: name, count of entries, entry size, zero'd sectors
            [DbStore_CONFIG_PATH]            = { "CONFIG"       , 1               , sizeof(struct LockConfig     ) },
            [DbStore_HOL_PATH]               = { "HOL"          , MAX_HOL         , sizeof(struct LockHol        ) },
            [DbStore_SCHED_PATH]             = { "SCHED"        , MAX_SCHED       , sizeof(struct LockSched      ) },
            [DbStore_SCHED_POLICY_PATH]      = { "SCHED_POLICY" , MAX_SCHED_POLICY, sizeof(struct LockSchedPolicy) },
            [DbStore_CRED_PATH]              = { "CRED"         , MAX_CRED        , sizeof(struct LockCred       ), 2 },
            [DbStore_EVT_PRIORITY_PATH]      = { "EVT_PRIORITY" , MAX_EVT         , sizeof(struct LockEvt        ), 2 },
            [DbStore_EVT_NON_PRIORITY_PATH]  = { "EVT_NORMAL"   , MAX_EVT         , sizeof(struct LockEvt        ), 2 },
        }};
    
#endif

#include "DbStore.h"
#include "KernelCharacterBuffer.h"
#include <zephyr/fs/fcb.h>
#include <assert.h>

struct Events
{
    Events(struct device *dev, bool doClear = false)
    {
        int f_area_id = FIXED_PARTITION_ID(event_normal);
        fcb_init(f_area_id, &file);
        if (doClear)
            fcb_clear(&file);
    }

    void write(struct LockEvt const& evt);
    void send(KCB& kcb, unsigned n);
private:
    struct fcb file;
};

void Events::write(struct LockEvt const& evt)
{
    // need to allocate area to write the data
    // NB: all returns return NZ for error
    struct fcb_entry loc;
    fcb_append(&file, sizeof(evt), &loc);

    // write the data to flash via flash area API
    flash_area_write(file.fap, FCB_ENTRY_FA_DATA_OFF(loc), &evt, sizeof(evt));
    
    // write checksum to validate data
    fcb_append_finish(&file, &loc);
}

void Events::send(KCB& kcb, unsigned n)
{
    // C++ is serious about type matching: second arg must by `void *`
    struct args { KCB& kcb; unsigned n; } arg {kcb, n};
    auto kcb_append = [](struct fcb_entry_ctx *entry_ctx, void *p) -> int
        {
            struct LockEvt evt;
            auto arg_p = static_cast<args *>(p);

            // get length from context. should be sizeof(evt)
            assert(entry_ctx->loc.fe_data_len == sizeof(evt));
            flash_area_read(entry_ctx->fap,
                            FCB_ENTRY_FA_DATA_OFF(entry_ctx->loc),
                            &evt,
                            sizeof(evt));
            
            // serialize
            //KCB.append(evt)
            
            // decrement count. return nz if end
            return --arg_p->n;
        };
    
    fcb_walk(&file, nullptr, kcb_append, &arg);    
}