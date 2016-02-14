/*
** calloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:08 2016 Adrien WERY
** Last update	Thu Feb 11 11:21:28 2016 Adrien WERY
*/

#include "malloc.h"

void    *my_memset(void *ptr, char c, size_t size)
{
    char    *d;

    d = ptr;
    while (--size)
        *d++ = c;
    return (ptr);
}

void    *calloc(size_t nb, size_t size)
{
    void    *ptr;
    size_t  fullSize;

    fullSize = nb * size;
    DEBUG(write(1, "calloc\n", 7));
    R_NULL(!(ptr = malloc(fullSize)));
    DEBUG(write(1, "callocE\n", 8));
    return (my_memset(ptr, 0, fullSize));
}
