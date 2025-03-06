#include "stdio.h"
 #include <unistd.h>
#include "../include/ft_malloc.h"
#include "../libft/libft.h"

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
    void* ptr[6];

    printf("Pagesize: 0x%x\n-----------------\n", getpagesize());
    ptr[0] = malloc(0x210);
    ft_bzero(ptr[0], 0x210);
    ptr[1] = malloc(0x110);
    ft_bzero(ptr[1], 0x110);
    ptr[2] = malloc(0x50);
    ft_bzero(ptr[2], 0x50);
    ptr[3] = malloc(0x133);
    ft_bzero(ptr[3], 0x133);
    ptr[4] = malloc(0x341);
    ft_bzero(ptr[4], 0x341);
    getchar();
    show_alloc_mem_ex();
    printf("-----------------\n");
    free(ptr[1]);
    free(ptr[3]);
    show_alloc_mem_ex();
    free(ptr[2]);
    printf("-----------------\n");
    getchar();
    ptr[1] = malloc(0x28);
    ft_bzero(ptr[1], 8);
    ptr[2] = malloc(0x21);
    ft_bzero(ptr[2], 0x1);
    ptr[3] = malloc(0x21);
    ft_bzero(ptr[3], 0x20);
    ptr[5] = malloc(0x219);
    ft_bzero(ptr[5], 0x200);
    show_alloc_mem_ex();
    free(ptr[0]);
    free(ptr[4]);
    printf("-----------------\n");
    getchar();
    show_alloc_mem_ex();
    printf("-----------------\n");
    free(ptr[1]);
    free(ptr[2]);
    free(ptr[3]);
    show_alloc_mem_ex();
    free(ptr[5]);
    getchar();
    show_alloc_mem_ex();
    return 0;
}
