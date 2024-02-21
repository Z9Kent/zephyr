#include <zephyr/kernel.h>
#include "Z9Message.h"

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

LockMsg_IPB ipb;
LockMsg_LATCH latch;
LockObj_Privacy priv;

int main(void)
{
        printk("Z9Exec::main()\n");
        printk("priv:registered() -> %x\n", priv.registered());
        printk("ipb:index() -> %d\n", ipb.index());
        printk("latch:index() -> %d\n", latch.index());
        priv.exec(&ipb);
        priv.exec(&latch);
        printk("direct exec: ");
        priv(&ipb);
        return 0;
}
