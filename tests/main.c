#include "stdio.h"
 #include <unistd.h>
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
    printf("Pagesize: 0x%x\n-----------------\n", getpagesize());

    void* ptr = ft_malloc(0x210);
    
    printf("ptr: %p\n-----------------\n", ptr);
    show_alloc_mem();
    ft_free(ptr);
    printf("-----------------\n");
    show_alloc_mem();
    return 0;
}
