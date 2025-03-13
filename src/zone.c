#include "malloc_intrnl.h"
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
    zone->magic = ZONE_MAGIC;
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
    if (zone->magic != ZONE_MAGIC)
        return;
    if (context->mode & M_MODE_PERFORMANCE 
        && (!zone->next && !zone->prev))
        return;
    LIST_UNLINK(chunk, context->zoneChunks[chunk->zoneType])
    unmapZone(context, zone);   
}

char ptrInMappedZone(t_context* context, void* ptr)
{
    t_zone* zone;
    t_zone_type zoneType = zone_tiny;

    while (zoneType <= zone_large)
    {
        zone = context->zones[zoneType];
        while (zone)
        {
            if (ptr > (void*)zone
                && ptr < (void*)(zone + zone->size))
                return 1;
            zone = zone->next;
        }
        zoneType++;
    }
    return 0;
}