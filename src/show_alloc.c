#include "malloc_intrnl.h"

static void print_large_allocation(t_large_chunk* largeChunk)
{
    char* data;
    
    data = (char*)SKIP_STRUCT(largeChunk, t_large_chunk, 1);
    ft_printf("%p - %p : %i bytes\n", 
        data, 
        data + largeChunk->used, 
        largeChunk->used
    );
}

static void print_allocation(t_chunk* chunk)
{
    char* data;

    data = (char*)SKIP_STRUCT(chunk, t_chunk, 1);
    if (chunk->inUse)
    {
        ft_printf("%p - %p : %i bytes\n", 
            data, 
            data + chunk->used, 
            chunk->used
        );
    }
}

static void print_zone(t_zone* zone)
{
    static const char* zoneTypes[] = {
        "TINY",
        "SMALL",
        "LARGE"
    };

    ft_printf("%s : %p\n", zoneTypes[zone->type], zone);
}

void show_alloc_mem()
{
    t_context* context = getContext();
    t_callbacks callbacks = {
        print_zone,
        print_allocation,
        print_large_allocation
    };
    releaseContext(context);

    loopZones(context, &callbacks);
    ft_printf("Total : %i bytes\n", context->memoryUsed);
}
