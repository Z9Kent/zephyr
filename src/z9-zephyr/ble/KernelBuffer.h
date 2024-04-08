// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.

/**
 * @file KernelBuffer.h
 * @brief KernelBuffer
 * A KernelBuffer is a kernel-managed buffer that is used at the application layer for whatever purposes the application layer needs.
 * In a limited-memory embedded environment, this serves as a dynamic, but bounded way, of managing memory.
 *
 * In the Zephyr environment, the raw memory allocation is managed as system "Memory Slab". The KernelBuffer layer
 * is used to record allocations and implement the "reference" abstraction.
 *
 */

#pragma once

#include <zephyr/kernel.h>
#include <zephyr/sys/slist.h>
#include <stddef.h>

// TODO: pull from KConfig
#define KernelBuffer_BLOCK_SIZE  128
//#define KernelBuffer_NUM_BLOCKS   30
#define KernelBuffer_NUM_BLOCKS   10

#ifdef __cplusplus
extern "C" {
#endif

// KernelBuffer is just raw memory
struct KernelBuffer
{
    union
    {
        struct KernelBuffer *next_p;
        sys_snode_t          node;
        uint8_t              data[KernelBuffer_BLOCK_SIZE];
    };
};

// declare internal types
typedef const char *z9_error_t;
typedef uint8_t     KB_ref_t;

// use of MACROs allows for tracing of allocations
#define KernelBuffer_alloc(pResult) KernelBuffer_alloc_impl(pResult, __FILE__, __LINE__)
z9_error_t KernelBuffer_alloc_impl(struct KernelBuffer **pResult, const char *file, unsigned lineNo); ///< allocate and set reference count to 1.
z9_error_t KernelBuffer_free      (struct KernelBuffer *); ///< decrement reference count. deallocate if zero.
z9_error_t KernelBuffer_freeList  (struct KernelBuffer *first, struct KernelBuffer *last);  ///< Return linked list of blocks to free linked list
z9_error_t KernelBuffer_allocRaw  (struct KernelBuffer **pResult);
z9_error_t KernelBuffer_setInfo   (struct KernelBuffer *, const char *file, unsigned lineNo);

// manipulate the reference count
z9_error_t KernelBuffer_addReference  (struct KernelBuffer *); ///< increment reference count
z9_error_t KernelBuffer_referenceCount(struct KernelBuffer *, KB_ref_t *pResult); ///< get reference count.

// for flow control
unsigned KernelBuffer_availableBufferCount(void); ///< get the count of available buffers.

// inspection routines used for logging & debug
unsigned KernelBuffer_getId (struct KernelBuffer *);
void KernelBuffer_dumpAllocs(void);

#ifdef __cplusplus
}
#endif
