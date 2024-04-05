
#pragma once


#include "Z9IO_Device.h"
#include "Z9Crypto_gcm.h"

#include "KernelCharacterBuffer.h"

#include <zephyr/kernel.h>
#include <zephyr/sys/slist.h>

#include <array>
#include <stdint.h>

#define NUM_Z9IO_LINK 2

// declare signature of inbound method
struct Z9IO_Link;
using Z9IO_inbound = void (*)(void *data, Z9IO_Link const&, KCB&);

// declare internal states
enum Z9IO_Link_State : uint8_t {
          LS_INIT
        , LS_WAIT_HELLO         // remote init
        , LS_PEND_BOARD_INFO    // remote pending send
        , LS_WAIT_BOARD_INFO    // controller init
        , LS_KEY_XCHANGE_WAIT   // remote waiting key exchange
        , LS_KEY_XCHANGE_PEND   // remote pending send
        , LS_IDLE               // normal-response-mode
        , LS_WAIT               // RNR (not yet implemented)
        , NUM_Z9IO_Link_State
};

static const char * const Z9IO_Link_State_str [NUM_Z9IO_Link_State] = {
      [LS_INIT]            = "INIT"
    , [LS_WAIT_HELLO]      = "WAIT_HELLO"
    , [LS_PEND_BOARD_INFO] = "PEND_BOARD_INFO"
    , [LS_WAIT_BOARD_INFO] = "WAIT_INFO"
    , [LS_KEY_XCHANGE_WAIT] = "KEY_XCG_WAIT"
    , [LS_KEY_XCHANGE_PEND] = "KEY_XCG_PEND"
    , [LS_IDLE]             = "IDLE"
    , [LS_WAIT]             = "WAIT"
};

// TBD: KeyStore object
// TBD: Z9IO Protocol Message object
// TBD: CRC16-methods
// TBD: GcmCrypto
// TBD: KCB C-class
// TBD: KernelCharacterBuffer.c, KernelBuffer.c



struct Z9IO_Link
{
//private:
    // controlled lifecycle
    Z9IO_Link(unsigned ordinal, const struct device *);
    //~Z9IO_Link() = delete;

public:
    static Z9IO_Link& get(unsigned ordinal);
    unsigned          unit() const { return _unit; }
    void              xmit(KCB& kcb);
    void              set_inbound(Z9IO_inbound fn, void *data);  

private:
    // workq C-compatible callbacks
    static void xmit_trampoline (struct k_work *cb);
    static void recv_trampoline (struct k_work *cb);

    // C++ workq methods
    void xmit_return   (KCB& kcb);
    bool recv_return   (KCB& kcb);
    void recv_keyexchange(KCB& kcb);

    // implement FSM
    void set_timeout(unsigned msec = 1000);
    void xmit_fsm_loop();

    // ident
    unsigned id() const;
    
    // declare transmit queue
    //kcb_t                *xmit_queue_head;
    //kcb_t               **xmit_queue_tail;
    KCB                 *xmit_kcb, *recv_kcb;

    // device I/O interface
    struct z9io_device   *dev;

    // Inbound interface
    Z9IO_inbound        inbound;
    
    // Zephyr interface objects
    K_WORK_DEFINE      (xmit_work, xmit_trampoline);
    K_WORK_DEFINE      (recv_work, recv_trampoline);
    sys_slist_t         xmit_queue;

    // save the state bytes for last
    uint16_t            xmit_crc, recv_crc;
    uint8_t             seq_number; 
    uint8_t             _unit;
    Z9IO_Link_State     state;
    uint8_t             retry_count;
    bool                ack_pending;
    bool                encrypted_req;
    
    // define ordinal -> instance mapping for get
    static inline std::array<Z9IO_Link *, NUM_Z9IO_LINK> pInstances;
};

// temp home for support routines
extern uint8_t link_key[16], session_key[16];
// mimic old code
extern uint8_t local_seed[16], gcm_key[16];
extern gcm_key_id_t psa_link_key;
