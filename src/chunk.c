#include "malloc_intrnl.h"

t_zone* chunkGetZone(t_context* context, t_chunk* chunk)
{
    t_zone* zone;

    if (chunk->zoneType == zone_tiny)
        return (t_zone*)ALIGN(chunk, getpagesize());
    zone = context->zones[chunk->zoneType];
    while (zone)
    {
        if ((char*)chunk > (char*)zone 
            && (char*)chunk < (char*)zone + zone->size)
            return zone;
        zone = zone->next;
    }
    return NULL;
}

t_chunk* setupFreeChunk(t_context* context, char* addr, t_zone_type type, size_t size)
{
    t_chunk* chunk;

    chunk = (t_chunk*)addr;
    ft_bzero(chunk, sizeof(t_chunk));
    chunk->zoneType = type;
    chunk->inUse = 0;
    chunk->prevInUse = 0;
    chunk->size = size;
    *CHUNK_END_SIZE(chunk) = size;
    LIST_LINK(chunk, context->zoneChunks[chunk->zoneType])
    return chunk;
}

void fuzeNeighbourChunks(t_context* context, t_chunk* chunk)
{
    (void)context;
    (void)chunk;
    return ;
}

t_chunk* findFreeChunk(t_context* context, t_zone_type type, size_t size)
{
    t_chunk* chunk;

    chunk = context->zoneChunks[type];
    if (!chunk)
        return NULL;
    while (chunk)
    {
        if (chunk->size >= size)
            return chunk;
        chunk = chunk->next;
    }
    return NULL;
}

t_chunk* allocateChunk(t_context* context, t_chunk* freeChunk, size_t size)
{
    t_chunk* chunk;
    t_chunk* leftOverChunk;

    chunk = (t_chunk*)freeChunk;
    LIST_UNLINK(freeChunk, context->zoneChunks[freeChunk->zoneType])
    chunk->inUse = 1;
    chunk->used = size; 
    size = ALIGN_UP(size, 8) + sizeof(t_chunk) - LINK_SIZE;
    if (freeChunk->size - size < sizeof(t_chunk))
    {
        chunk->size = freeChunk->size; 
        NEXT_CHUNK(chunk)->prevInUse = 1;
    }
    else
    {
        leftOverChunk = setupFreeChunk(
            context,
            (char*)chunk + size,
            chunk->zoneType,
            freeChunk->size - size
        );
        leftOverChunk->prevInUse = 1;
        ft_printf("Chunk at %p -> 0x%x\n", leftOverChunk, leftOverChunk->size);
        chunk->size = size; 
    }
    ft_printf("Allocated Chunk at %p -> 0x%x\n", chunk, chunk->size);
    return chunk;
}

void freeChunk(t_context* context, t_chunk* chunk)
{
    chunk->inUse = 0;
    chunk->used = 0;
    NEXT_CHUNK(chunk)->prevInUse = 0;
    ft_bzero(chunk->data, sizeof(chunk->data));
    LIST_LINK(chunk, context->zoneChunks[chunk->zoneType])
}

t_chunk* mapChunk(t_context* context, t_zone_type type)
{
    t_zone* zone;
    t_chunk* freeChunk;
    t_chunk* boundaryChunk;

    zone = mapZone(context, type, 0);
    if (!zone)
        return NULL;
    boundaryChunk = (t_chunk*)SKIP_STRUCT(zone, t_zone, 1);
    ft_bzero(boundaryChunk, sizeof(t_chunk) - LINK_SIZE);
    boundaryChunk->zoneType = zone_boundary;
    boundaryChunk->size = sizeof(t_chunk) - LINK_SIZE;
    freeChunk = setupFreeChunk(
        context, 
        (char*)boundaryChunk + boundaryChunk->size,
        type, 
        zone->size - sizeof(t_zone) - (sizeof(t_chunk) - LINK_SIZE)
    );
    boundaryChunk = NEXT_CHUNK(freeChunk);
    ft_bzero(boundaryChunk, sizeof(t_chunk) - LINK_SIZE);
    boundaryChunk->size = sizeof(t_chunk) - LINK_SIZE;
    boundaryChunk->zoneType = zone_boundary;
    return freeChunk;
}
