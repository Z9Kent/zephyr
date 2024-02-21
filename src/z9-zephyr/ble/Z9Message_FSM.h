// Z9Message_FSM.h C++

#pragma once

#include "Z9Message.h"

using namespace kas;

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
