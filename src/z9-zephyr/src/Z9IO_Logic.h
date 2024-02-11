// Z9IO_Logic.h

#pragma once

#include "KernelCharacterBuffer.h"
#include "Z9IO_Link.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/slist.h>

#include <array>
#include <cstdint>


struct Z9IO_Logic
{
    Z9IO_Logic();
    static Z9IO_Logic& get(unsigned ordinal);

    void recv(KCB&);
    void send(KCB&);

private:
    static void recv_fn(struct k_work *);
    void process_recv(KCB&);

    uint8_t _unit;

    K_WORK_DEFINE(recv_work, recv_fn);
    sys_slist_t   recv_queue;
    
    // define ordinal -> instance mapping for get
    static inline std::array<Z9IO_Logic *, NUM_Z9IO_LINK> pInstances;

};