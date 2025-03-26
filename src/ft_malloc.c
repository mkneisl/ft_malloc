#include "malloc_intrnl.h"

void free(void *ptr)
{
    t_context* context;
    t_chunk* chunk;
    t_lrg_chunk* largeChunk;

    if (!ptr)
        return;
    context = getContext();
#ifdef __APPLE__
    if (!ptrInMappedZone(context, ptr))
    {
        releaseContext(context);
        return;
    }
#endif
    if ((uint64_t)ptr % 8)
    {
        ft_putstr_fd("free(): invalid pointer\n", 1);
        if (context->mode & M_MODE_ABRT)
            abort();
        releaseContext(context);
        return;
    }
    context->stats.freeCallC++;
    largeChunk = NULL;
    chunk = (t_chunk*)SKIP_STRUCT(ptr, size_t, -1);
    if (chunk->zoneType == zone_large)
    {
        largeChunk = (t_lrg_chunk*)SKIP_STRUCT(ptr, t_lrg_chunk, -1);
        context->stats.allocationCount--;
        context->stats.memoryUsed -= largeChunk->used;
        unmapLargeChunk(context, largeChunk);
        releaseContext(context);
        return;
    }
    freeChunk(context, chunk);
    chunk = fuzeNeighbourChunks(context, chunk);
    unmapEmptyZone(context, chunk);
    releaseContext(context);
    return; 
}

void *calloc(size_t nelem, size_t elsize)
{
    void* ptr;

    ptr = malloc(nelem * elsize);
    if (!ptr)
       return NULL;
    ft_bzero(ptr, nelem * elsize);
    return ptr;
}

size_t malloc_size(const void* ptr)
{
    t_lrg_chunk* largeChunk;
    t_chunk* chunk;
   
    largeChunk = NULL;
    chunk = (t_chunk*)SKIP_STRUCT(ptr, size_t, -1);
    if (chunk->zoneType == zone_large)
    {
        largeChunk = (t_lrg_chunk*)SKIP_STRUCT(ptr, t_lrg_chunk, -1);
        return largeChunk->used;
    }
    return chunk->used;
}

void *malloc(size_t size)
{
    t_context* context;
    t_zone_type zoneType;
    t_chunk* availChunk;
    t_lrg_chunk* largeChunk;

    if (!size)
        return NULL;
    context = getContext();
    context->stats.mallocCallC++;
    availChunk = NULL;
    if (size > MAX_SMALL_ALLOC)
    {
        largeChunk = mapLargeChunk(context, size);
        if (!largeChunk)
        {
            releaseContext(context);
            return NULL;
        }
        context->stats.allocationCount++;
        context->stats.memoryUsed += size;
        releaseContext(context);
        return SKIP_STRUCT(largeChunk, t_lrg_chunk, 1);
    }
    zoneType = size <= MAX_TINY_ALLOC ? zone_tiny : zone_small;
    availChunk = findFreeChunk(context, zoneType, ALIGN_UP(size + sizeof(size_t), 8));
    if (!availChunk)
    {
        if (!(availChunk = mapChunk(context, zoneType)))
        {
            releaseContext(context);
            return NULL;
        }
    }
    allocateChunk(context, availChunk, size);
    releaseContext(context);
    return availChunk->data;
}

void *realloc(void *ptr, size_t size)
{
    t_context* context;
    t_chunk* chunk;
    t_lrg_chunk* largeChunk;
    void* data;

    if (!ptr)
        return malloc(size);
    if (!size)
        return free(ptr), NULL;
    context = getContext();
#ifdef __APPLE__
    if (!ptrInMappedZone(context, ptr))
    {
        releaseContext(context);
        return NULL;
    }
#endif
    if ((uint64_t)ptr % 8)
    {
        if (context->mode & M_MODE_ABRT)
            abort();
        releaseContext(context);
        return NULL;
    }
    context->stats.reallocCallC++;
    largeChunk = NULL;
    chunk = (t_chunk*)SKIP_STRUCT(ptr, size_t, -1);
    if (chunk->zoneType == zone_large)
    {
        largeChunk = (t_lrg_chunk*)SKIP_STRUCT(ptr, t_lrg_chunk, -1);
        largeChunk = expandLargeChunk(context, largeChunk, size);
        if (!largeChunk)
        {
            releaseContext(context);
            return NULL;
        }
        releaseContext(context);
        return SKIP_STRUCT(largeChunk, t_lrg_chunk, 1);
    }
    if (chunk->size - sizeof(t_chunk) >= size)
    {
        context->stats.memoryUsed += size - chunk->used;
        chunk->used = size;
        releaseContext(context);
        return ptr;
    }
    if (enlargeChunk(context, chunk, size))
    {
        releaseContext(context);
        return chunk->data;
    }
    releaseContext(context);
    data = malloc(size);
    if (!data)
        return NULL;
    getContext();
    ft_memmove(data, chunk->data, chunk->used);
    releaseContext(context);
    free(chunk->data);
    return data;
}

