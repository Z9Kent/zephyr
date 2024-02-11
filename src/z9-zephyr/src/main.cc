#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>
#include <exception>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
    printk("z9lock: %s\n", __func__);

    #if 0
    try {
        for(;;) k_yield();
    }
    catch (const std::exception& e)
    {
        LOG_ERR("exception: %s", e.what());
        k_panic();
    }
    #endif
    return 0;
}