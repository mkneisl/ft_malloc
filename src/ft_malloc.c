#include "malloc_intrnl.h"
#include "stdio.h"

void free(void *ptr)
{
    t_context* context;
    t_chunk* chunk;
    t_large_chunk* largeChunk;

    context = getContext();
    if (!ptr)
        return;
    largeChunk = NULL;
    chunk = (t_chunk*)SKIP_STRUCT(ptr, size_t, -1);
    if (chunk->zoneType == zone_large)
    {
        largeChunk = (t_large_chunk*)SKIP_STRUCT(ptr, t_large_chunk, -1);
        context->allocationCount--;
        context->memoryUsed -= largeChunk->used;
        unmapLargeChunk(context, largeChunk);
        return;
    }
    freeChunk(context, chunk);
    chunk = fuzeNeighbourChunks(context, chunk);
    unmapEmptyZone(context, chunk);
    releaseContext(context);
}

void *malloc(size_t size)
{
    t_context* context;
    t_zone_type zoneType;
    t_chunk* availChunk;
    t_large_chunk* largeChunk;

    context = getContext();
    availChunk = NULL;
    if (size > MAX_SMALL_ALLOC)
    {
        largeChunk = mapLargeChunk(context, size);
        if (!largeChunk)
            return NULL;
        context->allocationCount++;
        context->memoryUsed += size;
        return SKIP_STRUCT(largeChunk, t_large_chunk, 1);
    }
    zoneType = size <= MAX_TINY_ALLOC ? zone_tiny : zone_small;
    availChunk = findFreeChunk(context, zoneType, ALIGN_UP(size + sizeof(size_t), 8));
    if (!availChunk)
    {
        if (!(availChunk = mapChunk(context, zoneType)))
            return NULL;
    }
    allocateChunk(context, availChunk, size);
    releaseContext(context);
    return availChunk->data;
}

void *realloc(void *ptr, size_t size)
{
    t_context* context;
    t_chunk* chunk;
    t_large_chunk* largeChunk;
    //t_chunk* availChunk;
    void* data;

    context = getContext();
    if (!ptr)
        return NULL;
    largeChunk = NULL;
    chunk = (t_chunk*)SKIP_STRUCT(ptr, size_t, -1);
    if (chunk->zoneType == zone_large)
    {
        largeChunk = expandLargeChunk(context, largeChunk, size);
        if (!largeChunk)
            return NULL;
        return SKIP_STRUCT(largeChunk, t_large_chunk, 1);
    }
    if (chunk->size - sizeof(t_chunk) >= size)
    {
        context->memoryUsed += size - chunk->used;
        chunk->used = size;
        return ptr;
    }
    context->memoryUsed -= chunk->used;
    if (enlargeChunk(context, chunk, size))
    {
        context->memoryUsed += chunk->used;
        return chunk->data;
    }
    // availChunk = findFreeChunk(context, chunk->zoneType, ALIGN_UP(size + sizeof(size_t), 8));
    // if (!availChunk)
    // {
    //     if (!(availChunk = mapChunk(context, chunk->zoneType)))
    //         return NULL;
    // }
    // ft_memmove(availChunk->data, chunk->data, chunk->used);
    // freeChunk(context, chunk);
    releaseContext(context);
    data = malloc(size);
    if (!data)
        return NULL;
    context = getContext();
    ft_memmove(data, chunk->data, chunk->used);
    freeChunk(context, chunk);
    return data;
}

