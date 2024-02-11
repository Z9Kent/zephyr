#include "kas_string.h"
#include <zephyr/sys/printk.h>

#include <meta/meta.hpp>
#include <cstdint>

#pragma once

using namespace kas;

// NB: Need list of all LockMsg types for two reasons:
// 1) Message serialized as `Index` in message 
// 2) Object records supported Messages as bitmap (on index)

// Declare all "LockMsg" types.
using ALL_LockMsg = meta::list<
      struct LockMsg_IPB
    , struct LockMsg_LATCH
    , struct LockMsg_DPS
    , struct LockMsg_DeadBolt
    >;

// number of message types is size of list
static constexpr auto NUM_LockMsg = ALL_LockMsg::size();

struct MessageObject_ABC
{
    virtual const char *name() const = 0;
    virtual const std::size_t size() const = 0;
    virtual const uint16_t index() const = 0;
    virtual ~MessageObject_ABC() {}
};

template <typename T, typename NAME=KAS_STRING("Dummy Msg")>
struct LockMessageBase : MessageObject_ABC
{
    T&       derived()       { return *static_cast<T*>(this); }
    T const& derived() const { return *static_cast<const T*>(this); }
    
    const char *name() const override { return NAME(); }
    const std::size_t size() const override { return sizeof(T); }
    const uint16_t   index() const override
    {
        using index_t = meta::find_index<ALL_LockMsg, T>;
        static_assert(!std::is_same_v<index_t, meta::npos>,
                     "Message type must be listed in `ALL_LockMsg`");
        return index_t::value;
    }
};

struct LockObject_ABC 
{
    using ExecFn_t = void (*)(LockObject_ABC&, MessageObject_ABC *);

    LockObject_ABC(ExecFn_t fn) { exec_fn = fn; }
    virtual const char    *name() const = 0;
    virtual const std::size_t    size() const = 0;
    virtual const uint16_t registered() const = 0;

    // pass `LockMsg` to `LockObject` instance
    void exec(MessageObject_ABC *msg) { exec_fn(*this, msg); }
     
    virtual ~LockObject_ABC() {}
private:
    ExecFn_t exec_fn;
};


template <typename T, typename NAME=KAS_STRING("Dummy Obj")>
struct LockObjectBase : LockObject_ABC
{
    // initalize the abstrace base class
    LockObjectBase () : LockObject_ABC (exec_as_obj) {}

    T&       derived()       { return *static_cast<T*>(this); }
    T const& derived() const { return *static_cast<const T*>(this); }
    
    const char       *name() const override { return NAME(); }
    const std::size_t size() const override { return sizeof(T); }

    const uint16_t registered() const override;
    void  exec(MessageObject_ABC *msg);

private:
    static void exec_as_obj(LockObject_ABC& ref, MessageObject_ABC *msg)
        { static_cast<LockObjectBase&>(ref).exec(msg); }

};

// XXX not required to list `Objects`, just `Messages`
using ALL_LockObj = meta::list<
     struct LockObj_Exec
   , struct LockObj_Latch
   , struct LockObj_Privacy
   >;


// sample message
struct LockMsg_IPB : LockMessageBase<LockMsg_IPB, KAS_STRING("IPB")>
{
    bool active;
};


struct LockMsg_LATCH : LockMessageBase<LockMsg_LATCH, KAS_STRING("LATCH")> {};


struct LockObj_Privacy : LockObjectBase<LockObj_Privacy, KAS_STRING("PRIVACY")>
{
    void operator()(LockMsg_IPB *msg)
    {
        printk("%s: object received msg %s\n", name(), msg->name());

        active ^= true;
        // send LockMsg_Display(priv-on or something);
    }

    bool active;
};

extern LockMsg_IPB ipb;
extern LockMsg_LATCH latch;
extern LockObj_Privacy priv;
