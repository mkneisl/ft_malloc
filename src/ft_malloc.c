#include "malloc_intrnl.h"
t_arena arena;
#include "stdio.h"

void ft_free(void *ptr)
{
    t_free_chunk* pChunk;

    if (!ptr)
        return;
    pChunk = (t_free_chunk*)((char*)ptr - sizeof(t_chunk));
    if (pChunk->info.m)
    {
        destroyMappedChunk(pChunk);
        return;
    }
}

void *ft_malloc(size_t size)
{
    t_free_chunk* targetChunk;

    targetChunk = NULL;
    if (size < LARGE_ALLOC)
    {
        t_heap* heap = createHeap(&arena, HEAP_MAX_SIZE);
        printf("Heap at %p -> %lx %x \n", heap, heap->size, HEAP_MAX_SIZE);
    }
    else
    {
        targetChunk = createMappedChunk(&arena, size);
    }
    // Find & Reserve fitting chunk

 
    if (targetChunk)
        return &targetChunk->next;
    return NULL;
}

void *ft_realloc(void *ptr, size_t size)
{
    (void)ptr;
    (void)size;
    return NULL;
}
