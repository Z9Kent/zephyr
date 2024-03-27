// Z9IO_Logic.h

#pragma once

#include "KernelCharacterBuffer.h"
#include "Z9IO_Link.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/slist.h>

#include <array>
#include <cstdint>

#include "Z9Lock_status.h"
#include "Z9LockIO_ECDH.h"

struct Z9IO_Logic
{
    Z9IO_Logic();
    static Z9IO_Logic& get(unsigned ordinal);

    void recv(KCB&);
    void send(KCB&);

private:
    static void recv_fn(struct k_work *);
    bool process_recv(KCB&);        // true if buffer consumed

    uint8_t _unit;

    K_WORK_DEFINE(recv_work, recv_fn);
    sys_slist_t   recv_queue;
    
    // define ordinal -> instance mapping for get
    static inline std::array<Z9IO_Logic *, NUM_Z9IO_LINK> pInstances;

};

void send_hostInfo(uint64_t sn);
void send_hostStatus(Z9Lock_status const&);
void send_passThru(KCB& );
void send_req_ecdh(ECDH_rsp_fn, const uint8_t *key, uint16_t keyLength);

// declare passthru destinations
void z9lockio_recv(KCB&);
void eros_send(KCB&);
