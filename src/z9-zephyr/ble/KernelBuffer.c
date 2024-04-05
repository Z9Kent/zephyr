// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.

/**
 * @file KernelBuffer.c
 */

#include "KernelBuffer.h"
#include <zephyr/logging/log.h>
#include <assert.h>

LOG_MODULE_REGISTER(KernelBuffer, LOG_LEVEL_DBG);

// internal data structures
struct KernelBufferInfo_t
{
    uint8_t referenceCount;
    const char *file;
    unsigned lineNo;
};

// create private handle to buffer "slab"
static struct k_mem_slab kb_slab;
static struct KernelBufferInfo_t kernelBufferInfo[KernelBuffer_NUM_BLOCKS];

// allocate KernelBuffer memory at compile time
K_MEM_SLAB_DEFINE_STATIC(kb_slab, KernelBuffer_BLOCK_SIZE, KernelBuffer_NUM_BLOCKS, sizeof(void *));

z9_error_t KernelBuffer_allocRaw(struct KernelBuffer **pResult)
{
    // use Zephyr to allocate memory from slab
    if (k_mem_slab_alloc(&kb_slab, (void **)pResult, K_NO_WAIT))
    {
        LOG_ERR("%s: slab allocation failed", __func__);
        KernelBuffer_dumpAllocs();
        return "KernelBuffer: memory exhausted";
    }
    return NULL;
}

z9_error_t KernelBuffer_setInfo(struct KernelBuffer *buf, const char *file, unsigned lineNo)
{
    // update accounting with buffer allocation information
    struct KernelBufferInfo_t *pInfo = &kernelBufferInfo[KernelBuffer_getId(buf)];
    pInfo->referenceCount = 1;
    pInfo->file = file;
    pInfo->lineNo = lineNo;
    return NULL;
}

z9_error_t KernelBuffer_alloc_impl(struct KernelBuffer **pResult, const char *file, unsigned lineNo)
{
    z9_error_t err = KernelBuffer_allocRaw(pResult);
    if (!err)
        err = KernelBuffer_setInfo(*pResult, file, lineNo);
    return err;
}

// so debug hits right breakpoint
static void log_zeroReference(const char *fn, void *buf)
{
    LOG_ERR("%s: %p: zero referenceCount", fn, buf);
}

z9_error_t KernelBuffer_free(struct KernelBuffer *buf)
{
    // decrement reference count & deallocate if count is zero
    struct KernelBufferInfo_t *pInfo = &kernelBufferInfo[KernelBuffer_getId(buf)];

    // validate count non-zero
    if (!pInfo->referenceCount)
        log_zeroReference(__func__, buf);
    if (!pInfo->referenceCount)
        KernelBuffer_dumpAllocs();

    // return to system if count reduced to zero
    if (!--pInfo->referenceCount)
        k_mem_slab_free(&kb_slab, buf);
    
    return NULL;
}

z9_error_t KernelBuffer_freeList(struct KernelBuffer *first, struct KernelBuffer *last)
{
    //printk("%s: from %p -> %p: ", __func__, first, last);
    struct KernelBuffer *buf;
    do 
    {
        buf = first;
        first = first->next_p;

        //printk("%p, ", buf);
        z9_error_t err = KernelBuffer_free(buf);
        if (err)
        {
            //printk(": -> error: %s\n", err);
            return err;
        }
    } while (buf != last);
    //printk(": done\n");
    return NULL;
}

z9_error_t KernelBuffer_addReference(struct KernelBuffer *buf)
{
    struct KernelBufferInfo_t *pInfo = &kernelBufferInfo[KernelBuffer_getId(buf)];
    ++pInfo->referenceCount;
    return NULL;
}

unsigned KernelBuffer_getId(struct KernelBuffer *buf)
{
    struct KernelBuffer *base = (void *)kb_slab.buffer;
    unsigned id = buf - base;
    if (buf != &base[id])
        LOG_ERR("%s: Invalid buffer pointer: %p", __func__, buf);
    if (id >= KernelBuffer_NUM_BLOCKS)
        LOG_ERR("%s: Buffer ID out-of-range: %u", __func__, id);
    return id;
}

void KernelBuffer_dumpAllocs(void)
{
    // for each allocated buffer, display where allocated
    struct KernelBufferInfo_t *pInfo = kernelBufferInfo;
    struct KernelBuffer *base = (void *)kb_slab.buffer;

    LOG_INF("%s: buffer base address: %p", __func__, base);
    for (unsigned n = 0; n < KernelBuffer_NUM_BLOCKS; ++n, ++pInfo)
        if (pInfo->referenceCount)
            LOG_INF("%s: %u allocated at %s:%u", __func__, n, 
                            pInfo->file ?: "???", pInfo->lineNo);
}

// Zephyr memory slabs are inited PRE_KERNEL_1, KERNEL_INIT_PRIORITY_OBJECTs
// No local initialization required: SYS_INIT(KernelBuffer_init, PRE_KERNEL_1, KERNEL_INIT_PRIORITY_DEFAULT);