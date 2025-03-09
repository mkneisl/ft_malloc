#include "malloc_intrnl.h"
#include "errno.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

t_zone* mapZone(t_context* context, t_zone_type type, size_t size)
{
    t_zone* zone;
    void* mapped;

    if (type == zone_tiny)
        size = TINY_ZONE_SIZE;
    if (type == zone_small)
        size = SMALL_ZONE_SIZE;
    mapped = mmap(NULL,
        size, 
        PROT_READ | PROT_WRITE, 
        MAP_ANONYMOUS | MAP_PRIVATE | MAP_NORESERVE, 
        -1, 0
    );
    context->stats.mmapCallC++;
    if (mapped == (void*)-1)
        return 0;
    context->stats.memoryMapped += size;
    zone = (t_zone*)mapped;
    ft_bzero(zone, sizeof(t_zone));
    zone->context = context;
    zone->size = size;
    zone->type = type;
    LIST_LINK(zone, context->zones[zone->type])
    return zone;
}

void unmapZone(t_context* context, t_zone* zone)
{
    LIST_UNLINK(zone, context->zones[zone->type])
    context->stats.memoryMapped -= zone->size;
    munmap(zone, zone->size);
    context->stats.munmapCallC++;
}

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

void unmapEmptyZone(t_context* context, t_chunk* chunk)
{
    t_chunk* prevChunk;
    t_zone* zone;

    prevChunk = (t_chunk*)SKIP_STRUCT(chunk, size_t, -1);
    if (prevChunk->zoneType != zone_boundary)
        return;
    if (NEXT_CHUNK(chunk)->zoneType != zone_boundary)
       return;
    zone = (t_zone*)SKIP_STRUCT(prevChunk, t_zone, -1);
    if (!zone->next && !zone->prev)
        return;
    LIST_UNLINK(chunk, context->zoneChunks[chunk->zoneType])
    unmapZone(context, zone);   
}

t_context* getContext()
{
    static t_context context = { 0 };

    if (!context.mtxInit)
    {
        pthread_mutex_init(&context.mtx, NULL);
        context.mtxInit = 1;
    }
    pthread_mutex_lock(&context.mtx);
    return &context;
}

void releaseContext(t_context* context)
{
    pthread_mutex_unlock(&context->mtx);
}

