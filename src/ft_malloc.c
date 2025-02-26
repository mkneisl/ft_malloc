#include "malloc_intrnl.h"
#include "stdio.h"

void ft_free(void *ptr)
{
    t_context* context;
    t_chunk* chunk;
    t_large_chunk* largeChunk;

    context = getContext();
    if (!ptr)
        return;
    largeChunk = NULL;
    chunk = (t_chunk*)SKIP_STRUCT(ptr, t_chunk, -1);
    if (chunk->zoneType == zone_large)
    {
        largeChunk = (t_large_chunk*)SKIP_STRUCT(ptr, t_large_chunk, -1);
        unmapLargeChunk(context, largeChunk);
        return;
    }
    freeChunk(context, chunk);
    fuzeNeighbourChunks(context, chunk);
}

void *ft_malloc(size_t size)
{
    t_context* context;
    t_zone_type zoneType;
    t_chunk* freeChunk;
    t_large_chunk* largeChunk;
    t_chunk* allocation;

    context = getContext();
    freeChunk = NULL;
    if (size > MAX_SMALL_ALLOC)
    {
        largeChunk = mapLargeChunk(context, size);
        if (!largeChunk)
            return NULL;
        return SKIP_STRUCT(largeChunk, t_large_chunk, 1);
    }
    zoneType = size <= MAX_TINY_ALLOC ? zone_tiny : zone_small;

    // Find & Reserve fitting chunk
    freeChunk = findFreeChunk(context, zoneType, size + sizeof(t_chunk));
    if (!freeChunk)
        if (!(freeChunk = mapChunk(context, zoneType)))
            return NULL;
    allocation = allocateChunk(context, freeChunk, size);
    if (allocation)
        return SKIP_STRUCT(allocation, t_chunk, 1);
    return NULL;
}

void *ft_realloc(void *ptr, size_t size)
{
    (void)ptr;
    (void)size;
    return NULL;
}

