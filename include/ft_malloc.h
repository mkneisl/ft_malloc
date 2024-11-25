#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# include <stdlib.h>

void ft_free(void *ptr);
void *ft_malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);
#endif
