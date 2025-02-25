#ifndef MALLOC_INTRNL_H
# define MALLOC_INTRNL_H
# include <stdint.h>
# include "../include/ft_malloc.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define ALIGN_UP(val, align) (((uint64_t)val + (align - 1)) & ~(align - 1))
# define SKIP_STRUCT(ptr, struct, dir) (void*)((struct*)ptr + dir)

# define MAX_TINY_ALLOC 0x20
# define MAX_SMALL_ALLOC 0x500

# define TINY_ZONE_SIZE ALIGN_UP(MAX_TINY_ALLOC * 100, getpagesize()) 
# define SMALL_ZONE_SIZE ALIGN_UP(MAX_SMALL_ALLOC * 100, getpagesize())

typedef struct s_context t_context;

typedef enum e_zone_type
{
    zone_tiny,
    zone_small,
    zone_large,
}t_zone_type;

typedef struct s_chunk
{
    size_t size : 31;
    size_t used : 30;
    size_t inUse : 1;
    t_zone_type zoneType : 2;
}t_chunk;

typedef struct s_large_chunk
{
    size_t size;
    size_t used : 62;
    t_zone_type zoneType : 2;
}t_large_chunk;

typedef struct s_free_chunk
{
    t_chunk info;
    struct s_free_chunk* next;
    struct s_free_chunk* prev;
}t_free_chunk;

typedef struct s_zone
{
    t_context* context;
    struct s_zone* next;
    struct s_zone* prev;
    size_t size : 62;
    t_zone_type type : 2;
}t_zone;

typedef struct s_context
{
    //mutex
    t_zone*       zones[3];
    t_free_chunk* zoneChunks[3];
}t_context;

t_zone* mapZone(t_context* context, t_zone_type type, size_t size);
void unmapZone(t_context* context, t_zone* zone);

t_large_chunk* mapLargeChunk(t_context* context, size_t size);
void unmapLargeChunk(t_context* context, t_large_chunk* mappedChunk);

t_context* getContext();

#endif
