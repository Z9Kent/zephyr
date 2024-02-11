#include <zephyr/kernel.h>
#include "Z9Message.h"

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
