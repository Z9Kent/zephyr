
#pragma once
#include <stdint.h>


extern "C"
{
    struct LockEvt
    {
        uint16_t id;
        uint32_t time;
    };
}