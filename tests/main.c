#include "stdio.h"
#include "../include/ft_malloc.h"

void *mcalloc(size_t size)
{
    void* ptr = malloc(size);
    for (size_t i = 0; i < size; i++)
    {
        ((char*)ptr)[i] = 0;
    }
    return ptr;
}

int main()
{
    printf("Wtf\n");
    void* ptr = ft_malloc(1024);

    printf("ptr: %p\n", ptr);
    free(ptr);
    return 0;
}
