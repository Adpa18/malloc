/*
** calloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:08 2016 Adrien WERY
** Last update	Fri Feb 05 22:51:12 2016 Adrien WERY
*/

#include "malloc.h"

void    *calloc(size_t nb, size_t size)
{
    void    *ptr;
    size_t  fullSize;

    fullSize = nb * size;
    if (!(ptr = malloc(fullSize)))
        return (NULL);
    return (memset(ptr, 0, fullSize));
}
