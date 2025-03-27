#include "libft.h"
#include "ft_malloc.h"
#include <time.h>
#include <stdlib.h>

void memIntegrityTest(unsigned int mCount)
{
    void* arr[100000];
    size_t sizes[100000];

    if (mCount > 100000)
        mCount = 100000;
    srand(time(NULL));
    for (unsigned int a = 0; a < mCount; a++)
    {
        sizes[a] = rand() % 0xFFFF;
        arr[a] = malloc(sizes[a]);
        ft_printf("[%i]Malloced(%5li) %p\n", a, sizes[a], arr[a]);
        if ((uint64_t)arr[a] % 16)
        {
            ft_printf("Error malloc not 16 byte aligned\n");
            return;
        }
        for (size_t b =0; b < sizes[a]; b++)
            ((char*)arr[a])[b] = 0x42;
    }
    for (unsigned int a = 0; a < mCount; a++)
    {
        for (size_t b = 0; b < sizes[a]; b++)
        {
            if (((char*)arr[a])[b] != 0x42)
            {
                ft_printf("Error bytes not equal\n");
                return;
            }
        }
        ft_printf("[%i]Freeing %p\n", a, arr[a]);
        free(arr[a]);
    }
    ft_printf("Freed ptrs\n");
}

int main(int argc, char** argv)
{
    int def = 1000;

    if (argc > 1)
        def = ft_atoi(argv[1]);
    memIntegrityTest(def);
    show_alloc_mem_ex();
}