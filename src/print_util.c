#include "malloc_intrnl.h"
#include <stdio.h>

t_zone* findNextHigherZone(t_zone* list, t_zone* prevZone)
{
    size_t diff = 0;
    size_t smallestDiff = 0;
    t_zone* nextHigherZone = NULL;

    while (list)
    {
        if (list < prevZone
        || prevZone == list)
        {
            list = list->next;
            continue;
        }
        diff = (char*)list - (char*)prevZone;
        if (!smallestDiff || diff < smallestDiff)
        {
            smallestDiff = diff;
            nextHigherZone = list;
        }
        list = list->next;
    }
    return nextHigherZone;
}
 
void loopAllocations(t_zone* zone, t_callbacks* callbacks)
{
    t_chunk* chunk;

    chunk = (t_chunk*)SKIP_STRUCT(zone, t_zone, 1);
    while ((char*)chunk < ((char*)zone + zone->size))
    {
        callbacks->print_alloc(chunk);
        chunk = NEXT_CHUNK(chunk);
    }
}

void loopZones(t_context* context, t_callbacks* callbacks)
{
    t_zone* zone;
    t_large_chunk* largeChunk;
    t_zone_type zoneType = zone_tiny;

    while (zoneType <= zone_large)
    {
        zone = findNextHigherZone(context->zones[zoneType], NULL);
        while (zone)
        {
            callbacks->print_zone(zone);
            if (zone->type == zone_large)
            {
                largeChunk = (t_large_chunk*)SKIP_STRUCT(zone, t_zone, 1);
                callbacks->print_large_alloc(largeChunk);
            }
            else
                loopAllocations(zone, callbacks);
            zone = findNextHigherZone(context->zones[zoneType], zone);
        }
        zoneType++;
    }
}
