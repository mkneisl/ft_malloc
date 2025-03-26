#include "stdio.h"
#include <unistd.h>
#include "../include/ft_malloc.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>

char* bee(char* ee)
{
return ee +5;
}

void memIntegrityTest()
{
    void* arr[100000];
    size_t sizes[100000];

    srand(time(NULL));
    for (int a =0; a < 100000; a++)
    {
        sizes[a] = rand() % 0xFF;
        arr[a] = malloc(sizes[a]);
        printf("[%i]Malloced(%li) %p\n",a, sizes[a], arr[a]);
        for (size_t b =0; b < sizes[a]; b++)
            ((char*)arr[a])[b] = 0x42;
    }
    for (int a =0; a < 1000; a++)
    {
        for (size_t b = 0; b < sizes[a]; b++)
        {
            if (((char*)arr[a])[b] != 0x42)
                printf("Error bytes not equal\n");
        }
        free(arr[a]);
    }
}


int main()
{
    void* ptr[6];

    ft_printf("Pagesize: 0x%x\n-----------------\n", getpagesize());
    ft_printf("Ptr: %p\n", malloc(42));
    //ft_printf("Ptr: %p\n", malloc(2));
    //ft_printf("Ptr: %p\n", malloc(13));
    ft_printf("Ptr: %p\n", malloc(92));
    ft_printf("Ptr: %p\n", malloc(55));
    show_alloc_mem_ex();
    return 0;
    memIntegrityTest();
    getchar();
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
    free((ptr[1] ));
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
