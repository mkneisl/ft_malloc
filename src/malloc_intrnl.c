#include "malloc_intrnl.h"
#include <sys/mman.h>
#include "stdio.h"
#include "errno.h"
#include <string.h>
#include <unistd.h>
#include "stdio.h"

void binAddFreeChunk(t_arena* pArena, t_chunk* pChunk)
{
    t_free_chunk* pFreeChunk;

    pFreeChunk = (t_free_chunk*)pChunk;
    if (!pArena->binFirst)
    {
        pArena->binFirst = pFreeChunk;
        pArena->binLast = pFreeChunk;
        pFreeChunk->next = (t_free_chunk*)&pArena->binFirst;
        pFreeChunk->prev = (t_free_chunk*)&pArena->binFirst;
        return;
    }
    pArena->binFirst->prev = pFreeChunk;
    pFreeChunk->prev = (t_free_chunk*)&pArena->binFirst;
    pFreeChunk->next = pArena->binFirst;
    pArena->binFirst = pFreeChunk;
}
//void createChunk(t_arena* pArena, )

t_free_chunk* initMappedHeapChunk(t_heap* pHeap)
{
    t_free_chunk* pChunk;
    
    pChunk = (t_free_chunk*)((char*)pHeap + sizeof(t_heap));
    pChunk->info.a = 1;
    pChunk->info.m = 1;
    pChunk->info.p = 1;
    pChunk->info.size = (pHeap->size - sizeof(t_heap)) / 8;
    return pChunk;
}

t_free_chunk* initHeapChunk(t_heap* pHeap)
{
    t_free_chunk* pChunk;
    
    pChunk = (t_free_chunk*)((char*)pHeap + sizeof(t_heap));
    pChunk->info.a = 1;
    pChunk->info.m = 0;
    pChunk->info.p = 1;
    pChunk->info.size = (pHeap->size - sizeof(t_heap)) / 8;
    return pChunk;
}

t_heap* createHeap(t_arena* pArena, size_t size)
{
    t_heap* pHeap;
    void* pMapped;
    size_t overlap;

    pMapped = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE | MAP_NORESERVE , -1, 0);
    if (pMapped == (void*)-1)
    {
        printf("mmap failed %i - %s\n", errno, strerror(errno));
        return 0;
    }
    pHeap = (t_heap*)ALIGN_UP(pMapped, HEAP_MAX_SIZE);
    overlap = (uint64_t)pHeap - (uint64_t)pMapped;
    if (munmap(pMapped, overlap) == -1)
    {
        printf("munmap failed %i - %s\n", errno, strerror(errno));
    }
    pHeap->pArena = pArena;
    pHeap->size = size - overlap;
    pHeap->prev = NULL;
    return pHeap;
}

t_free_chunk* createMappedChunk(t_arena* pArena, size_t size)
{
    t_heap* pHeap;

    size = size + sizeof(t_heap) + sizeof(t_chunk);
    size = ALIGN_UP(size, getpagesize());
    pHeap = createHeap(pArena, size);
    if (!pHeap)
    {
        return NULL;
    }
    return initMappedHeapChunk(pHeap);
}

void destroyMappedChunk(t_free_chunk* mappedChunk)
{
    destroyHeap((t_heap*)(mappedChunk - sizeof(t_heap)));
}

void destroyHeap(t_heap* pHeap)
{
    munmap(pHeap, pHeap->size);
}

t_arena* getContext()
{
    static bool intialized = false;

    
}
