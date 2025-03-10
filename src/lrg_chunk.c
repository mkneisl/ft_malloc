#include "malloc_intrnl.h"

t_lrg_chunk* mapLargeChunk(t_context* context, size_t size)
{
    t_lrg_chunk* largeChunk;
    t_zone* zone;
    size_t allocSize;

    allocSize = size;
    size = size + sizeof(t_zone) + sizeof(t_chunk);
    size = ALIGN_UP(size, getpagesize());
    zone = mapZone(context, zone_large, size);
    if (!zone)
    {
        return NULL;
    }
    largeChunk = (t_lrg_chunk*)SKIP_STRUCT(zone, t_zone, 1);
    largeChunk->zoneType = zone->type;
    largeChunk->used = allocSize;
    largeChunk->size = size;
    return largeChunk;
}

t_lrg_chunk* expandLargeChunk(t_context* context, t_lrg_chunk* largeChunk, size_t size)
{
    size_t mapSize;
    t_lrg_chunk* mappedChunk;

    if (largeChunk->size - sizeof(t_lrg_chunk) >= size)
    {
        context->stats.memoryUsed += size - largeChunk->used;
        largeChunk->used = size;
        return largeChunk;
    }
    mapSize = ALIGN_UP(size, 8) + sizeof(t_lrg_chunk);
    mappedChunk = mapLargeChunk(context, mapSize);
    if (!mappedChunk)
        return NULL;
    context->stats.memoryUsed += size - largeChunk->used;
    ft_memmove(
        SKIP_STRUCT(mappedChunk, t_lrg_chunk, 1),
        SKIP_STRUCT(largeChunk, t_lrg_chunk, 1),
        largeChunk->used);
    unmapLargeChunk(context, largeChunk);
    return mappedChunk;
}

void unmapLargeChunk(t_context* context, t_lrg_chunk* mappedChunk)
{
    unmapZone(context, SKIP_STRUCT(mappedChunk, t_zone, -1));
}
