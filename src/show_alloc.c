#include "malloc_intrnl.h"

t_zone* find_next_higher_zone(t_zone* list, t_zone* prevZone)
{
    size_t diff = 0;
    size_t smallestDiff = 0;
    t_zone* nextHigherZone = NULL;

    while (list)
    {
        if (list > prevZone)
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

void print_allocations(t_zone* zone, size_t* totalSize)
{
    char* data;
    t_chunk* chunk;

    chunk = (t_chunk*)SKIP_STRUCT(zone, t_zone, 1);
    while ((char*)chunk < ((char*)zone + zone->size))
    {
        data = (char*)SKIP_STRUCT(chunk, t_chunk, 1);
        if (chunk->inUse)
        {
            ft_printf("%p - %p : 0x%x bytes (0x%x)\n", 
                data, 
                data + chunk->used, 
                chunk->used,
                chunk->size
            );
            *totalSize += chunk->used;
        }
        chunk = (t_chunk*)((char*)chunk + chunk->size);
    }
}

void print_large_allocation(t_zone* zone, size_t* totalSize)
{
    char* data;
    t_large_chunk* largeChunk;

    largeChunk = (t_large_chunk*)SKIP_STRUCT(zone, t_zone, 1);
    data = (char*)SKIP_STRUCT(largeChunk, t_large_chunk, 1);
    ft_printf("%p - %p : %i bytes\n", 
        data, 
        data + largeChunk->used, 
        largeChunk->used
    );
    *totalSize += largeChunk->used;
}

void print_zone(t_zone* zone, size_t* totalSize)
{
    static const char* zoneTypes[] = {
        "TINY",
        "SMALL",
        "LARGE"
    };

    ft_printf("%s : %p\n", zoneTypes[zone->type], zone);
    if (zone->type != zone_large)
        print_allocations(zone, totalSize);
    else
        print_large_allocation(zone, totalSize);
}

void print_zones(t_context* context, size_t* totalSize)
{
    t_zone* zone;
    t_zone_type zoneType = zone_tiny;

    while (zoneType <= zone_large)
    {
        zone = context->zones[zoneType];
        while (zone)
        {
            print_zone(zone, totalSize);
            zone = zone->next;
        }
        zoneType++;
    }
}

void show_alloc_mem()
{
    size_t totalSize = 0;
    t_context* context = getContext();

    print_zones(context, &totalSize);
    ft_printf("Total : %i bytes\n", totalSize);
}
