#include "malloc_intrnl.h"
#include "stdio.h"

void ft_free(void *ptr)
{
    t_free_chunk* chunk;
    t_large_chunk* largeChunk;

    if (!ptr)
        return;
    largeChunk = NULL;
    chunk = (t_free_chunk*)SKIP_STRUCT(ptr, t_chunk, -1);
    if (chunk->info.zoneType == zone_large)
    {
        largeChunk = (t_large_chunk*)SKIP_STRUCT(ptr, t_large_chunk, -1);
        unmapLargeChunk(getContext(), largeChunk);
        return;
    }
}

void *ft_malloc(size_t size)
{
    t_free_chunk* targetChunk;
    t_large_chunk* largeChunk;

    targetChunk = NULL;
    if (size > MAX_SMALL_ALLOC)
    {
        largeChunk = mapLargeChunk(getContext(), size);
        if (!largeChunk)
            return NULL;
        return SKIP_STRUCT(largeChunk, t_large_chunk, 1);
    }
    t_zone_type zoneType = size <= MAX_TINY_ALLOC ? zone_tiny : zone_small;
    t_zone* zone = mapZone(getContext(), zoneType, 0);
    ft_printf("Heap at %p -> %lx \n", zone, (size_t)zone->size);
    // Find & Reserve fitting chunk

 
    if (targetChunk)
        return &targetChunk->next;
    return NULL;
}

void *ft_realloc(void *ptr, size_t size)
{
    (void)ptr;
    (void)size;
    return NULL;
}

