#include "stdio.h"
#include <unistd.h>
#include "../include/ft_malloc.h"
#include "libft.h"

char* invalidate(char* ee)
{
    return ee + 5;
}

void checkDefrag()
{
    void* ptr[6];

    ptr[0] = malloc(0x210);
    ft_bzero(ptr[0], 0x210);
    printf("ptr: %p\n", ptr[0]);
    ptr[1] = malloc(0x110);
    ft_bzero(ptr[1], 0x110);
    printf("ptr: %p\n", ptr[1]);
    ptr[2] = malloc(0x50);
    ft_bzero(ptr[2], 0x50);
    printf("ptr: %p\n", ptr[2]);
    ptr[3] = malloc(0x133);
    ft_bzero(ptr[3], 0x133);
    printf("ptr: %p\n", ptr[3]);
    ptr[4] = malloc(0x341);
    ft_bzero(ptr[4], 0x341);
    printf("ptr: %p\n", ptr[4]);
    show_alloc_mem_ex();
    ft_printf("---------------------\n");
    free((ptr[1]));
    free(ptr[3]);
    show_alloc_mem_ex();
    ft_printf("-----------------\n");
    ptr[0] = realloc(ptr[0], 0x340);
    ptr[2] = realloc(ptr[2], 0x100);
    show_alloc_mem_ex();
    ft_printf("ptr[0] %p\nptr[2] %p\n-----------------\n", ptr[0], ptr[2]);
    ptr[1] = malloc(0x28);
    ft_bzero(ptr[1], 8);
    ptr[3] = malloc(0x21);
    ft_bzero(ptr[3], 0x20);
    ptr[5] = malloc(0x219);
    ft_bzero(ptr[5], 0x200);
    show_alloc_mem_ex();
    ft_printf("-----------------\n");
    free(ptr[0]);
    free(ptr[4]);
    show_alloc_mem_ex();
    ft_printf("-----------------\n");
    free(ptr[1]);
    free(ptr[2]);
    free(ptr[3]);
    free(ptr[5]);
    show_alloc_mem();
}

void checkPrint()
{
    void* ptr[6];

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
    show_alloc_mem();
    free(ptr[1]);
    free(ptr[3]);
    show_alloc_mem();
    ptr[0] = realloc(ptr[0], 0x340);
    ptr[2] = realloc(ptr[2], 0x100);
    ptr[1] = malloc(0x28);
    ft_bzero(ptr[1], 8);
    ptr[3] = malloc(0x21);
    ft_bzero(ptr[3], 0x20);
    ptr[5] = malloc(0x219);
    ft_bzero(ptr[5], 0x200);
    show_alloc_mem();
    free(ptr[0]);
    free(ptr[4]);
    free(ptr[1]);
    show_alloc_mem();
    free(ptr[2]);
    free(ptr[3]);
    free(ptr[5]);
    show_alloc_mem();
}

int main()
{
    ft_printf("Pagesize: 0x%x\n-----------------\n", getpagesize());
    checkDefrag();
    checkPrint();
    //show_alloc_mem_ex();
    // free(invalidate(ptr[1]));
   
    
    // free((ptr[1]));
    // free(ptr[3]);
    // show_alloc_mem_ex();
    
    return 0;
}
