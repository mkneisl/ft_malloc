#include "malloc_intrnl.h"
#include "stdio.h"
#include "errno.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define LIST_LINK(node, start)  node->prev = NULL; \
                                if (start){ \
                                    start->prev = node;\
                                    node->next = start;\
                                }\
                                else\
                                    node->next = NULL;\
                                start = node;

#define LIST_UNLINK(node, start)    if (node->next) \
                                        node->next->prev = node->prev; \
                                    if (!node->prev) \
                                        start = node->next; \
                                    else \
                                        node->prev->next = node->next;

    //LIST_LINK(context->zoneChunks[chunk->info.zoneType], chunk)
    //LIST_UNLINK(chunk, context->zoneChunks[chunk->info.zoneType])

t_free_chunk* initZone(t_zone* zone)
{
    t_free_chunk* chunk;
    
    chunk = (t_free_chunk*)((char*)zone + sizeof(t_zone));
    ft_memset(chunk, 0, sizeof(t_free_chunk));
    chunk->info.zoneType = zone->type;
    chunk->info.inUse = 1;
    chunk->info.size = (zone->size - sizeof(t_zone)) / 8;
    return chunk;
}

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
    if (mapped == (void*)-1)
    {
        printf("mmap failed %i - %s\n", errno, strerror(errno));
        return 0;
    }
    printf("mmap %p\n", mapped);
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
    munmap(zone, zone->size);
}

t_large_chunk* mapLargeChunk(t_context* context, size_t size)
{
    t_large_chunk* largeChunk;
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
    largeChunk = (t_large_chunk*)SKIP_STRUCT(zone, t_zone, 1);
    largeChunk->zoneType = zone->type;
    largeChunk->used = allocSize;
    largeChunk->size = size;
    return largeChunk;
}

void unmapLargeChunk(t_context* context, t_large_chunk* mappedChunk)
{
    unmapZone(context, SKIP_STRUCT(mappedChunk, t_zone, -1));
}

t_context* getContext()
{
    static t_context context = {};

    return &context;
}
