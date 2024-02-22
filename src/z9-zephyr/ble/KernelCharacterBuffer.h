/*
 * kernel character buffer
 *
 * October 9, 2023
 */

#pragma once

#include "KernelBuffer.h"
#include <stdint.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

// declare types
typedef struct kcb kcb_t;
typedef uint8_t    kcb_headroom_t;
typedef uint32_t   kcb_offset_t;

// lifecycle
kcb_t      *kcb_allocate(kcb_headroom_t, const char *file , unsigned line);
z9_error_t  kcb_init_raw(kcb_t *, kcb_headroom_t);
z9_error_t  kcb_free    (kcb_t *);
z9_error_t  kcb_flush   (kcb_t *, kcb_headroom_t headroom);
z9_error_t  kcb_status  (kcb_t *);
uint16_t    kcb_ident   (kcb_t *);

// sequential access for data in buffer
z9_error_t  kcb_peek    (kcb_t *, uint8_t *);
z9_error_t  kcb_read    (kcb_t *, uint8_t *);
z9_error_t  kcb_write   (kcb_t *, uint8_t);
z9_error_t  kcb_load    (kcb_t *, uint8_t *, kcb_offset_t);

z9_error_t  kcb_readN   (kcb_t *, uint8_t **out, uint8_t *buf, uint16_t n, bool tryInPlace);

// control sequential r/w position
z9_error_t  kcb_top     (kcb_t *);
z9_error_t  kcb_curPos  (kcb_t *, kcb_offset_t *);
z9_error_t  kcb_seek    (kcb_t *, kcb_offset_t);
z9_error_t  kcb_skip    (kcb_t *, kcb_offset_t bytesToAdvance);

// access current block of kcb as raw data
uint8_t    *kcb_currentBlock(kcb_t *, kcb_headroom_t *bytesAvailable);


// examine buffer size & remaining r/w characters
kcb_offset_t kcb_size    (kcb_t *);
kcb_offset_t kcb_length  (kcb_t *);
bool         kcb_empty   (kcb_t *);

// header access
z9_error_t  kcb_push    (kcb_t *, uint8_t);
z9_error_t  kcb_pop     (kcb_t *, uint8_t *);

//static const kcb_headroom_t kcb_maxHeadroom(void);
static  uint8_t *kcb_allocHeadroom  (kcb_t *, kcb_headroom_t);
static  uint8_t *kcb_consumeHeadroom(kcb_t *, kcb_headroom_t);

// manipulate kernel queue locations
enum kcb_QUEUE { kcb_QUEUE_LINK, kcb_QUEUE_APPL, NUM_KCB_QUEUE };
void   kcb_addQueue(kcb_t *, enum kcb_QUEUE, kcb_t *toAdd);
kcb_t *kcb_popQueue(kcb_t *, enum kcb_QUEUE);


// The KernelCharacterBuffer (KCB) is a singly-linked-list of KernelBuffers.
// Each KernelBuffer is of fixed length (normally 128-bytes).
// The KCB consists of an initial block which holds the header + data, followed
// by blocks of data. 
//
// The first block of the KCB has several methods which support headers.
// First, the intial "headroom" is specified in the constructor and the "flush"
// routine. This is provide alignment and room for prefixes as might be required 
// for packets. 
//
// Second, the "allocHeadroom" and "consumeHeadroom" methods allow for the allocation
// and removal of a serialization header from the message.
//
// Other than these headroom operations, the KCB is designed to allow characters
// to be appended to the packet (via `kcb_write`) and then read (via `kcb_read`).
// 
// A KCB is initially in "write" mode. In this mode, writes are appended
//
// 
//
struct kcb
{
    struct KernelBuffer *next_p;
    struct KernelBuffer *rw_p;
    sys_snode_t          queue[NUM_KCB_QUEUE];
    //kcb_t               *queue[NUM_KCB_QUEUE];
    kcb_headroom_t       head_org;
    kcb_headroom_t       tail_cnt;
    kcb_headroom_t       read_end;
    kcb_headroom_t       read_cnt;
};


static inline uint8_t *kcb_allocHeadroom(kcb_t *kcb, kcb_headroom_t delta)
{
    kcb->head_org -= delta;
    __ASSERT(kcb->head_org >= sizeof(kcb_t), "%s: headroom not available", __func__);
    struct KernelBuffer *buf = (struct KernelBuffer *)kcb;
    return &buf->data[kcb->head_org];
}

static inline uint8_t *kcb_consumeHeadroom(kcb_t *kcb, kcb_headroom_t delta)
{
    kcb->head_org += delta;
    __ASSERT(kcb->head_org < sizeof(struct KernelBuffer), "%s: headroom not available", __func__);
    struct KernelBuffer *buf = (struct KernelBuffer *)kcb;
    return &buf->data[kcb->head_org - delta];
}

#ifdef __cplusplus
};

// Declare a C++ interface to the KernelCharacterBuffer type
#include <cstddef>
#include <stdexcept>
#include <new>

// define macro to creating KCBs
#define KCB_NEW(...)     new(__FILE__, __LINE__) KCB(__VA_ARGS__)

struct KCB
{
    using value_t  = uint8_t;
    using offset_t = kcb_offset_t;
    using error_t  = const char *;

    KCB (kcb_headroom_t h = 0)
    {
        // convert raw memory to KCB
        kcb_init_raw(*this, h);
    }

    ~KCB()
    {
        // release all resources except base page raw memory
        kcb_flush(*this, 0);
    }

    // allocate KCBs in KernelBuffer memory: record location
    static void *operator new(size_t, const char *file, unsigned line)
    {
        KernelBuffer *buf;
        if (error_t rc = KernelBuffer_alloc_impl(&buf, file, line))
            throw std::runtime_error{rc};
        return buf;
    }
    
    static void operator delete(void *p)
    {
        auto buf = static_cast<kcb_t *>(p);
        if (error_t rc = kcb_free(buf))
            throw std::runtime_error{rc};
    }

    // convert between KCB <=> kcb_t * for c-language support
    operator kcb_t *()       const { return const_cast<kcb_t *>(&data); }
    operator sys_snode_t *() const
    { 
        kcb_t *kcb = *this;
        return &kcb->queue[0];
    }

    uint16_t    id()     const       { return kcb_ident(*this); }
    error_t     status() const       { return kcb_status(*this); }
    KCB&        flush(kcb_headroom_t h) { return exec(kcb_flush, h); }
    
    // read & write
    value_t     read()              { return exec_v(kcb_read); }
    value_t     peek()              { return exec_v(kcb_peek); }
    KCB&        write(value_t c)    { return exec(kcb_write, c); }
    KCB&        load(uint8_t *p, offset_t n) { return exec(kcb_load, p, n); }
    
    uint8_t *   readN(uint8_t *buf, uint16_t n, bool tryInPlace=true)
                                    { return exec_v<uint8_t *>(kcb_readN, buf, n, tryInPlace); }

    // position, size, & length
    KCB&        top()               { return exec(kcb_top); }
    KCB&        seek(uint32_t pos)  { return exec(kcb_seek, pos); }
    KCB&        skip(uint32_t pos)  { return exec(kcb_skip, pos); }
    offset_t    curPos()            { return exec_v<offset_t>(kcb_curPos); }
    offset_t    size()   const      { return kcb_size(*this); }
    offset_t    length() const      { return kcb_length(*this); }
    bool        empty()  const      { return length() == 0; }
    
    // manipulate headroom
    value_t    *allocHeadroom(kcb_headroom_t h)   { return kcb_allocHeadroom(*this, h); }
    value_t    *consumeHeadroom(kcb_headroom_t h) { return kcb_consumeHeadroom(*this, h); }
    value_t     pop()               { return exec_v(kcb_pop);   }
    KCB&        push(uint8_t c)     { return exec(kcb_push, c); }

    // manipulate queue
    KCB        *topQUEUE(enum kcb_QUEUE);
    void        popQueue(enum kcb_QUEUE);
    KCB&        addQueue(enum kcb_QUEUE, KCB&);

    // method to access raw data blocks
    value_t    *currentBlock(kcb_headroom_t& bytesAvailable)
                                    { return kcb_currentBlock(*this, &bytesAvailable); }

//private:
    // trampoline to exec C-language functions
    template <typename FRT = error_t, typename...Args>
    KCB& exec(FRT (&fn)(kcb_t *, Args...), Args...args)
    {
        FRT rc = fn(*this, args...);
        if (rc) throw std::runtime_error{rc};
        return *this;
    }
    
    template <typename RT = value_t, typename FRT = error_t, typename...Args>
    RT exec_v(FRT (&fn)(kcb_t *, RT *, Args...), Args...args)
    {
        RT  result;
        FRT rc = fn(*this, &result, args...);
        if (rc) throw std::runtime_error{rc};
        return result;
    } 

    kcb_t   data;
};
#endif

