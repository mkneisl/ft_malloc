#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# include <stdlib.h>

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nelem, size_t elsize);

void show_alloc_mem();
void show_alloc_mem_ex();

#endif
