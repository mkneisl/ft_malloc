#include "malloc_intrnl.h"

static void print_large_allocation_ex(t_lrg_chunk* largeChunk)
{
    char* data;
    
    data = (char*)SKIP_STRUCT(largeChunk, t_lrg_chunk, 1);
    ft_printf("%p - %p : 0x%x bytes (0x%x used)\n", 
        data, 
        data + largeChunk->used, 
        largeChunk->size,
        largeChunk->used
    );
}

static void print_allocation_ex(t_chunk* chunk)
{
    if (chunk->zoneType == zone_boundary)
    {
        ft_printf("%p - %p : Boundary\n", 
            chunk, 
            (char*)chunk + chunk->size
        );
        return;
    }
    ft_printf("%p - %p : 0x%x bytes (0x%x used) InUse: %i\n", 
        chunk, 
        (char*)chunk + chunk->size, 
        chunk->size,
        chunk->used,
        chunk->inUse
    );
}

static void print_zone_ex(t_zone* zone)
{
    static const char* zoneTypes[] = {
        "TINY",
        "SMALL",
        "LARGE"
    };

    ft_printf("%s : %p - %p\n", zoneTypes[zone->type], zone,(char*)zone + zone->size);
}

void show_alloc_mem_ex()
{ 
    t_context* context = getContext();
    t_callbacks callbacks = {
        print_zone_ex,
        print_allocation_ex,
        print_large_allocation_ex
    };
    t_stats stats = context->stats;
    releaseContext(context);

    loopZones(context, &callbacks);
    ft_printf("Total Memory Used : 0x%x bytes\n", stats.memoryUsed);
    ft_printf("Total Memory Mapped : 0x%x bytes (%x pages)\n", stats.memoryMapped, stats.memoryMapped / getpagesize());
    ft_printf("Total Allocations : %i\n", stats.allocationCount);
    ft_printf("Total Malloc calls : %i\n", stats.mallocCallC);
    ft_printf("Total Realloc calls : %i\n", stats.reallocCallC);
    ft_printf("Total Free calls : %i\n", stats.freeCallC);
    ft_printf("Total mmap calls : %i\n", stats.mmapCallC);
    ft_printf("Total mumap calls : %i\n", stats.munmapCallC);
}
