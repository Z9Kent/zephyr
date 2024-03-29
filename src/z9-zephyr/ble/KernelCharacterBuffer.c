// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.
//
//  KernelCharacterBuffer.c
//

#include "KernelCharacterBuffer.h"
#include <string.h>
#include <zephyr/logging/log.h>

// share logging registration with KernelBuffer
LOG_MODULE_DECLARE(KernelBuffer, LOG_LEVEL_DBG);

// Forward declare utilities
static void kcb_end(kcb_t *);
static unsigned kcb_count(kcb_t *, struct KernelBuffer **last_p); // count number of blocks. Record last one

enum KCB_STATUS
{
    KCB_ERR_NONE,
    KCB_ERR_NO_BLOCK,
    KCB_ERR_RW_POS,
    KCB_ERR_PUSH,
    KCB_ERR_POP,
    NUM_KCB_STATUS
};

static z9_error_t kcb_errorStr(enum KCB_STATUS status)
{
    switch (status)
    {
    case KCB_ERR_NONE:
        return NULL;
    case KCB_ERR_NO_BLOCK:
        return "KCB: out-of-blocks";
    case KCB_ERR_RW_POS:
        return "KCB: invalid rw offset";
    case KCB_ERR_PUSH:
        return "KCB: invalid push";
    case KCB_ERR_POP:
        return "KCB: invalid pop";
    default:
        // zassert_false(NUM_KCB_STATUS, "KCB: invalid state: %u", status);
        break;
    }
    return "KCB: invalid state";
}

// add tracing
kcb_t *kcb_alloc_impl(uint8_t headroom, const char *file, unsigned lineNo)
{
    // `head_org` overloaded with status. Validate overload
    // zassert_true(NUM_KCB_STATUS < sizeof(kcb_t));

    struct KernelBuffer *buf;
    if (KernelBuffer_alloc_impl(&buf, file, lineNo))
    {
        // LOG_ERR("%s: %s returned NULL", __func__, "KernelBuffer_alloc");
        return NULL;
    }

    // build a `KCB` in the raw kernel buffer: initialize header
    kcb_t *kcb = (void *)buf;
    memset(kcb, 0, sizeof(struct kcb));
    kcb_flush(kcb, headroom);
    return kcb;
}

z9_error_t  kcb_init_raw(kcb_t *kcb, kcb_headroom_t h)
{
    // zero pointers & offsets
    memset(kcb, 0, sizeof(kcb_t));
    return kcb_flush(kcb, h);
}

z9_error_t kcb_flush(kcb_t *kcb, kcb_headroom_t headroom)
{
    // free additional blocks if they exist
    if (kcb->next_p)
    {
        kcb_end(kcb); // set rw_p to last block
        KernelBuffer_freeList(kcb->next_p, kcb->rw_p);
        kcb->next_p = NULL;
    }

    // initialize first (and only) block
    kcb->rw_p = (void *)kcb;
    kcb->head_org = sizeof(kcb_t) + headroom;
    kcb->tail_cnt = sizeof(struct KernelBuffer) - kcb->head_org;
    kcb->read_end = kcb->read_cnt = 0; // initially in `write` mode
    return NULL;                       // all OK
}

z9_error_t kcb_free(kcb_t *kcb)
{
    // free all linked blocks
    kcb_flush(kcb, 0);
    return KernelBuffer_free((struct KernelBuffer *)kcb);
}

z9_error_t kcb_link(kcb_t *kcb)
{
   KernelBuffer_addReference((struct KernelBuffer *)kcb);
   return 0;
}

uint8_t kcb_getLinks(kcb_t *kcb)
{
    KB_ref_t refs;
    KernelBuffer_referenceCount((struct KernelBuffer *)kcb, &refs);
    return refs;
}

uint16_t kcb_ident(kcb_t *kcb)
{
    return kcb ? KernelBuffer_getId((void *)kcb) : ~0;
}

z9_error_t kcb_status(kcb_t *kcb)
{
    return kcb->head_org < sizeof(kcb_t) ? kcb_errorStr(kcb->head_org) : NULL;
}

// set read pointer to first character location
// return pointer to first memory address
z9_error_t kcb_top(kcb_t *kcb)
{
    // ignore operation if buffer in error state
    if (kcb->head_org < sizeof(kcb_t))
        return kcb_errorStr(kcb->head_org);

    kcb->rw_p = (void *)kcb; // reading in first block

    // first block is `head_org` to end of BLOCK
    kcb->read_end = sizeof(struct KernelBuffer);
    kcb->read_cnt = kcb->read_end - kcb->head_org;

    // if only 1 block, just read to tail
    if (!kcb->next_p)
    {
        kcb->read_end -= kcb->tail_cnt;
        kcb->read_cnt -= kcb->tail_cnt;
    }
    return NULL;
}

// examine character at R/W pointer
z9_error_t kcb_peek(kcb_t *kcb, uint8_t *pChar)
{
    // if not in read mode, read from beginning
    if (kcb->read_end == 0)
        kcb_top(kcb);

    // if at end of current block, goto next block
    if (kcb->read_cnt == 0 && kcb->rw_p->next_p)
    {
        kcb->rw_p = kcb->rw_p->next_p;               // move RW to next block
        kcb->read_end = sizeof(struct KernelBuffer); // get offset to end of block
        kcb->read_cnt = sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *);
        // if last block, adjust read_* counts
        if (!kcb->rw_p->next_p)
        {
            kcb->read_end -= kcb->tail_cnt; // adjust end...
            kcb->read_cnt -= kcb->tail_cnt; // ...and count
        }
    }

    // if still at end -- reading past end
    if (kcb->read_cnt == 0)
    {
        // read past end is error
        kcb->head_org = KCB_ERR_RW_POS;
        LOG_WRN("%s: Error: %s (%d)", __func__, kcb_errorStr(kcb->head_org), (int)kcb->head_org);
        return 0;
    }

    // read character
    *pChar = kcb->rw_p->data[kcb->read_end - kcb->read_cnt];
    return NULL;
}

// update character at R/W pointer
z9_error_t kcb_poke(kcb_t *kcb, uint8_t c)
{
    // if not in read mode, read from beginning
    if (kcb->read_end == 0)
        kcb_top(kcb);

    // if at end of current block, goto next block
    if (kcb->read_cnt == 0 && kcb->rw_p->next_p)
    {
        kcb->rw_p = kcb->rw_p->next_p;               // move RW to next block
        kcb->read_end = sizeof(struct KernelBuffer); // get offset to end of block
        kcb->read_cnt = sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *);
        // if last block, adjust read_* counts
        if (!kcb->rw_p->next_p)
        {
            kcb->read_end -= kcb->tail_cnt; // adjust end...
            kcb->read_cnt -= kcb->tail_cnt; // ...and count
        }
    }

    // if still at end -- reading past end
    if (kcb->read_cnt == 0)
    {
        // read past end is error
        kcb->head_org = KCB_ERR_RW_POS;
        LOG_WRN("%s: Error: %s (%d)", __func__, kcb_errorStr(kcb->head_org), (int)kcb->head_org);
        return 0;
    }

    // update character 
    kcb->rw_p->data[kcb->read_end - kcb->read_cnt] = c;
    return NULL;
}

z9_error_t kcb_append(kcb_t *kcb, uint8_t c)
{
    // ignore operation if buffer in error state
    if (kcb->head_org < sizeof(kcb_t))
        return kcb_errorStr(kcb->head_org);

    // always place at end
    if (kcb->read_end)
        kcb_end(kcb);

    // test if room in buffer
    if (kcb->tail_cnt == 0)
    {
        // no room -- link in a new buffer block
        struct KernelBuffer *p;
        if (KernelBuffer_allocRaw(&p))
        {
            kcb->head_org = KCB_ERR_NO_BLOCK;
            LOG_ERR("%s: Error: %s (%d)", __func__, kcb_errorStr(kcb->head_org), (int)kcb->head_org);
            return kcb_errorStr(kcb->head_org);
        }

        kcb->rw_p->next_p = p; // add to linked list
        p->next_p = NULL;      // end linked list
        kcb->rw_p = p;         // record new RW buffer

        // next write is after "next" pointer.
        kcb->tail_cnt = sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *);
    }
    kcb->rw_p->data[sizeof(struct KernelBuffer) - kcb->tail_cnt--] = c;
    return NULL;
}

// push into headroom allocated when CharacterBuffer created
z9_error_t kcb_push(kcb_t *kcb, uint8_t c)
{
    // ignore operation if buffer in error state
    if (kcb->head_org < sizeof(kcb_t))
        return kcb_errorStr(kcb->head_org);

    struct KernelBuffer *p = (void *)kcb; // use KCB as block pointer
    if (kcb->head_org <= sizeof(kcb_t))
    {
        kcb->head_org = KCB_ERR_PUSH;
        LOG_ERR("%s: Error: %s (%d)", __func__, kcb_errorStr(kcb->head_org), (int)kcb->head_org);
        return kcb_errorStr(kcb->head_org);
    }
    else
    {
        p->data[--kcb->head_org] = c;
    }
    return NULL;
}

// pop from initial BLOCK
z9_error_t kcb_pop(kcb_t *kcb, uint8_t *pChar)
{
    struct KernelBuffer *p = (void *)kcb; // use KCB as block pointer

    // can only pop from first block
    // 1. if multiple blocks data valid thru end of block
    if (kcb->next_p)
    {
        if (kcb->head_org >= kcb->read_end)
            kcb->head_org = KCB_ERR_POP;
    }
    // 2. if single block, don't read past tail
    else if (kcb->head_org >= (sizeof(struct KernelBuffer) - kcb->tail_cnt))
        kcb->head_org = KCB_ERR_POP;

    // ignore operation if buffer in error state
    if (kcb->head_org >= sizeof(kcb_t))
        *pChar = p->data[kcb->head_org++];
    else
    {
        LOG_ERR("%s: Error: %s (%d)", __func__, kcb_errorStr(kcb->head_org), (int)kcb->head_org);
        return kcb_errorStr(kcb->head_org);
    }
    return NULL;
}

// non-destructive character read at R/W pointer
z9_error_t kcb_read(kcb_t *kcb, uint8_t *pChar)
{
    // if not in read mode, read from beginning
    if (kcb->read_end == 0)
        kcb_top(kcb);

    // if at end of current block, goto next block
    if (kcb->read_cnt == 0 && kcb->rw_p->next_p)
    {
        kcb->rw_p = kcb->rw_p->next_p;               // move RW to next block
        kcb->read_end = sizeof(struct KernelBuffer); // get offset to end of block
        kcb->read_cnt = sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *);
        // if last block, adjust read_* counts
        if (!kcb->rw_p->next_p)
        {
            kcb->read_end -= kcb->tail_cnt; // adjust end...
            kcb->read_cnt -= kcb->tail_cnt; // ...and count
        }
    }

    // if still at end -- reading past end
    if (kcb->read_cnt == 0)
    {
        // read past end is error
        kcb->head_org = KCB_ERR_RW_POS;
        LOG_ERR("%s: Error: %s (%d)", __func__, kcb_errorStr(kcb->head_org), (int)kcb->head_org);
        return kcb_errorStr(kcb->head_org);
    }

    // read character & update count
    *pChar = kcb->rw_p->data[kcb->read_end - kcb->read_cnt--];
    return NULL;
}

// for now, just loop
z9_error_t kcb_readN(kcb_t *kcb, uint8_t **out, uint8_t *in, uint16_t n, bool tryInPlace)
{
    *out = in;
    while (n-- > 1) kcb_read(kcb, in++);
    return kcb_read(kcb, in);
}

// overwrite character at R/W pointer
z9_error_t kcb_write(kcb_t *kcb, uint8_t c)
{
    // if not in read mode, read from beginning
    if (kcb->read_end == 0)
        kcb_top(kcb);

    // if at end of current block, goto next block
    if (kcb->read_cnt == 0 && kcb->rw_p->next_p)
    {
        kcb->rw_p = kcb->rw_p->next_p;               // move RW to next block
        kcb->read_end = sizeof(struct KernelBuffer); // get offset to end of block
        kcb->read_cnt = sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *);
        // if last block, adjust read_* counts
        if (!kcb->rw_p->next_p)
        {
            kcb->read_end -= kcb->tail_cnt; // adjust end...
            kcb->read_cnt -= kcb->tail_cnt; // ...and count
        }
    }

    // if at end of buffer, extend
    if (kcb->read_cnt == 0 && !kcb->rw_p->next_p)
    {
        // if room at end of current block, adjust counts
        if (kcb->tail_cnt)
        {
            --kcb->tail_cnt;
            ++kcb->read_cnt;
            ++kcb->read_end;
        }
        else
        {
            struct KernelBuffer *p;
            if (KernelBuffer_allocRaw(&p))
            {
                kcb->head_org = KCB_ERR_NO_BLOCK;
                LOG_ERR("%s: Error: %s (%d)", __func__, kcb_errorStr(kcb->head_org), (int)kcb->head_org);
                return kcb_errorStr(kcb->head_org);
            }
            
            kcb->rw_p->next_p = p;
            p->next_p = NULL;
            kcb->rw_p = p;

            // preadjust counts for write
            kcb->tail_cnt = sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *) - 1;
            kcb->read_end = sizeof(struct KernelBuffer *) + 1;
            kcb->read_cnt = 1;
        }
    }

    // write character & update count
    kcb->rw_p->data[kcb->read_end - kcb->read_cnt--] = c;
    return NULL;
}

// characters from head to tail
kcb_offset_t kcb_size(kcb_t *kcb)
{
    // ignore operation if buffer in error state
    if (kcb->head_org < sizeof(kcb_t))
        return 0;

    uint8_t n = kcb_count(kcb, NULL); // number of blocks

    // add count for added blocks
    // pick larger signed size to run down negative size buf
    int len = n * (sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *));

    // subtract out unoccupied slots at beginning and end
    len -= kcb->head_org + kcb->tail_cnt - sizeof(struct KernelBuffer *);
    __ASSERT(len >= 0, "%s: length is negative", __func__);
    return len;
}

kcb_offset_t kcb_length(kcb_t *kcb)
{
    // ignore operation if buffer in error state
    if (kcb->head_org < sizeof(kcb_t))
        return 0;

    // if write mode, length from head -> tail
    if (kcb->read_end == 0)
        return kcb_size(kcb);

    // if read mode, from read pointer -> end
    // XXX pick larger signed size to run down length < 0 bug
    int len = kcb->read_cnt; // remaining in current block;

    // add in full BLOCKS
    struct KernelBuffer *p = kcb->rw_p;
    if (p->next_p)
        len -= kcb->tail_cnt; // unused in last block

    // walk linked list for additional blocks
    while (p->next_p)
    {
        len += sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *);
        p = p->next_p;
    }
    __ASSERT(len >= 0, "%s: length is negative", __func__);
    return len;
}

z9_error_t kcb_curPos(kcb_t *kcb, kcb_offset_t *pCurPos)
{
    // ignore operation if buffer in error state
    if (kcb->head_org < sizeof(kcb_t))
        return kcb_errorStr(kcb->head_org);
    if (kcb->head_org < sizeof(kcb_t))
        return 0;

    // if write mode, curPos = head (ie zero)
    if (kcb->read_end == 0)
        return 0;

    // start with number in first block adjusted for unread in last
    // XXX pick larger signed size to run down negative length bug
    int len = sizeof(struct KernelBuffer) - kcb->head_org - kcb->read_cnt;

    // add in full BLOCKS
    // walk block from HEAD to current block
    struct KernelBuffer *p = (void *)kcb;

    while (p != kcb->rw_p)
    {
        len += sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *);
        p = p->next_p;
    }

    if (!p->next_p)
        len -= kcb->tail_cnt;

    __ASSERT(len >= 0, "%s: position is negative", __func__);
    *pCurPos = len;
    return NULL;
}

z9_error_t kcb_seek(kcb_t *kcb, kcb_offset_t loc)
{
    // ignore operation if buffer in error state
    if (kcb->head_org < sizeof(kcb_t))
        return kcb_errorStr(kcb->head_org);

    // be sure buffer is in read mode
    if (kcb->read_end == 0)
        kcb_top(kcb);

    const uint32_t locPassedIn = loc; // for logging
    // adjust loc so first block is "regular"
    loc += kcb->head_org;

    struct KernelBuffer *p = (void *)kcb;

    // first block size is different size
    uint32_t chars_per_block = sizeof(struct KernelBuffer);

    while (loc > chars_per_block)
    {
        // advance to next block if one
        if (!p->next_p)
        {
            uint32_t size = kcb_size(kcb);
            kcb->head_org = KCB_ERR_RW_POS;
            LOG_ERR("%s: locPassedIn=%u, loc=%u, size=%u, Error: %s (%d)", __func__, (unsigned int)locPassedIn, (unsigned int)loc, (unsigned int)size, kcb_errorStr(kcb->head_org), (int)kcb->head_org);
            return kcb_errorStr(kcb->head_org);
        }

        chars_per_block = sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *);
        loc -= chars_per_block;
        p = p->next_p;
    }

    // loc holds offset in block -- calculate end of this block
    // if not last block, then end is physical end of block
    kcb->rw_p = p;
    kcb->read_end = sizeof(struct KernelBuffer);

    // if last block, adjust end by `tail_cnt`
    if (!p->next_p)
        kcb->read_end -= kcb->tail_cnt;

    // error if loc past end of buffer, otherwise calculate position in block
    if (loc > kcb->read_end)
    {
        kcb->head_org = KCB_ERR_RW_POS;
        LOG_ERR("%s: locPassedIn=%u, loc=%u, read_end=%u, Error: %s (%d)", __func__, (unsigned int)locPassedIn, (unsigned int)loc, (unsigned int)kcb->read_end, kcb_errorStr(kcb->head_org), (int)kcb->head_org);
        return kcb_errorStr(kcb->head_org);
    }
    kcb->read_cnt = kcb->read_end - loc;
    return NULL;
}

// add data to end of block
z9_error_t kcb_load(kcb_t *kcb, const void *data, kcb_offset_t n)
{
    // dummy until bcopy version
    if (n == 0) return NULL;

    const uint8_t *p = data;
    while (--n) kcb_write(kcb, *p++);
    return kcb_write(kcb, *p);
}

// get pointer to raw data in current block
// used for access data as raw bytes for encryption processing
uint8_t *kcb_currentBlock(kcb_t *kcb, kcb_headroom_t *bytesAvailable)
{
    // if at end of current block, goto next block
    if (kcb->read_cnt == 0 && kcb->rw_p->next_p)
    {
        kcb->rw_p = kcb->rw_p->next_p;               // move RW to next block
        kcb->read_end = sizeof(struct KernelBuffer); // get offset to end of block
        kcb->read_cnt = sizeof(struct KernelBuffer) - sizeof(struct KernelBuffer *);
        // if last block, adjust read_* counts
        if (!kcb->rw_p->next_p)
        {
            kcb->read_end -= kcb->tail_cnt; // adjust end...
            kcb->read_cnt -= kcb->tail_cnt; // ...and count
        }
    }

    // now if count is zero, at EOF
    *bytesAvailable = kcb->read_cnt;
    if (!kcb->read_cnt)
        return NULL;

    // calculate pointer to beginning of data
    uint8_t *p = &kcb->rw_p->data[kcb->read_end - kcb->read_cnt];
    kcb->read_cnt = 0;      // consume all from this block
    return p;
}

z9_error_t kcb_skip(kcb_t *kcb, kcb_offset_t bytesToAdvance)
{
    kcb_offset_t curPos;
    kcb_curPos(kcb, &curPos);
    return kcb_seek(kcb, curPos + bytesToAdvance);
}

bool kcb_empty(kcb_t *kcb)
{
    // report buffer in error state as empty
    if (kcb->head_org < sizeof(kcb_t))
        return kcb_errorStr(kcb->head_org);
    if (kcb->head_org < sizeof(kcb_t))
        return true;

    // if write mode, test single block & head_org + tail_cnt = BLOCK_SIZE
    if (kcb->read_end == 0)
    {
        return !kcb->next_p && (kcb->head_org + kcb->tail_cnt) == sizeof(struct KernelBuffer);
    }

    // buffer in read mode -- test tail_cnt && rw_p->next
    return !kcb->rw_p->next_p && kcb->read_cnt == 0;
}

//
// internal support methods to walk buffer linked list
//
void kcb_end(kcb_t *kcb)
{
    kcb_count(kcb, &kcb->rw_p); // set rw_p to last block
    kcb->read_end = 0;          // put buffer in write mode
}

unsigned kcb_count(kcb_t *kcb, struct KernelBuffer **last_p)
{
    struct KernelBuffer *p = (void *)kcb;

    // idiom to count non-empty linked list
    unsigned n = 1;
    while (p->next_p)
    {
        p = p->next_p;
        ++n;
    }

    // save pointer to end if requested
    if (last_p)
        *last_p = p;

    // length of linked list
    return n;
}
