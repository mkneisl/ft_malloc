#include "libft.h"
#include "ft_malloc.h"
#include "../src/malloc_intrnl.h"

int main(int argc, char** argv)
{
    void* ptrs[100];
    int allocSize = 0;

    if (argc > 1)
        allocSize = ft_atoi(argv[1]);
    if (!allocSize)
        return 1;
    if (allocSize == 1)
        allocSize = MAX_TINY_ALLOC;
    else if (allocSize == 2)
        allocSize = MAX_SMALL_ALLOC;
    else if (allocSize == 3)
        allocSize = MAX_SMALL_ALLOC + 1;
    else
        return 1;
    for (int i = 0; i < 100; i++)
        ptrs[i] = malloc(allocSize);
    show_alloc_mem();
    for (int i = 0; i < 100; i++)
        free(ptrs[i]);
}
