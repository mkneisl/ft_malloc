#include "stdio.h"
#include <unistd.h>
#include "../include/ft_malloc.h"
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"

void *mcalloc(size_t size)
{
    void* ptr = malloc(size);
    for (size_t i = 0; i < size; i++)
    {
        ((char*)ptr)[i] = 0;
    }
    return ptr;
}

char* bee(char* ee)
{
return ee +5;
}

int main()
{
    void* ptr[6];

    ft_printf("Pagesize: 0x%x\n-----------------\n", getpagesize());
    show_alloc_mem_ex();
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
    show_alloc_mem_ex();
    ft_printf("-----------------\n");
    free(bee(ptr[1] ));
    free(ptr[3]);
    show_alloc_mem_ex();
    ft_printf("-----------------\n");
    ptr[0] = realloc(ptr[0], 0x340);
    ptr[2] = realloc(ptr[2], 0x100);
    ft_printf("ptr[0] %p\nptr[2] %p\n-----------------\n", ptr[0], ptr[2]);
    ptr[1] = malloc(0x28);
    ft_bzero(ptr[1], 8);
    ptr[3] = malloc(0x21);
    ft_bzero(ptr[3], 0x20);
    ptr[5] = malloc(0x219);
    ft_bzero(ptr[5], 0x200);
    show_alloc_mem_ex();
    free(ptr[0]);
    free(ptr[4]);
    ft_printf("-----------------\n");
    show_alloc_mem_ex();
    ft_printf("-----------------\n");
    free(ptr[1]);
    free(ptr[2]);
    free(ptr[3]);
    free(ptr[5]);
    show_alloc_mem_ex();
    return 0;
}
