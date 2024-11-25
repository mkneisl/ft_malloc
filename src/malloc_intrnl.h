#ifndef MALLOC_INTRNL_H
# define MALLOC_INTRNL_H
# include <stdint.h>
# include "../include/ft_malloc.h"

// https://elixir.bootlin.com/glibc/glibc-2.23/source/malloc/arena.c#L24
# define HEAP_MIN_SIZE (32 * 1024)
# ifndef HEAP_MAX_SIZE
#  ifdef DEFAULT_MMAP_THRESHOLD_MAX
#   define HEAP_MAX_SIZE (2 * DEFAULT_MMAP_THRESHOLD_MAX)
#  else
#   define HEAP_MAX_SIZE (1024 * 1024) /* must be a power of two */
#  endif
# endif

# define LARGE_ALLOC HEAP_MIN_SIZE
# define SMALL_ALLOC 0
# define TINY_ALLOC 0

# define ALIGN_UP(val, align) (((uint64_t)val + (align - 1)) & ~(align - 1))

typedef struct s_chunk
{
    size_t size : 61;
    size_t a : 1;
    size_t m : 1;
    size_t p : 1;
}t_chunk;

typedef struct s_free_chunk
{
    t_chunk info;
    struct s_free_chunk* next;
    struct s_free_chunk* prev;
}t_free_chunk;

typedef struct s_arena
{
    //mutex
    void* heapTop;
    t_free_chunk* binFirst;
    t_free_chunk* binLast;
    struct s_arena* next;
}t_arena;

typedef struct s_heap
{
    t_arena* pArena;
    //struct s_heap* next;
    struct s_heap* prev;
    size_t size;
}t_heap;

t_heap* createHeap(t_arena* pArena, size_t size);
void destroyHeap(t_heap* pHeap);

t_free_chunk* createMappedChunk(t_arena* pArena, size_t size);
void destroyMappedChunk(t_free_chunk* mappedChunk);

t_arena* getContext();
#endif
