/*
** realloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:23 2016 Adrien WERY
** Last update	Fri Feb 05 22:51:48 2016 Adrien WERY
*/

#include "malloc.h"

void    *realloc(void *ptr, size_t size)
{
    void    *new;

    if (!(new = malloc(size + 1)))
        return (NULL);
    if (!ptr)
        return (new);
    memcpy(new, ptr, ((t_block *)((size_t)ptr - BLOCK_SIZE))->size);
    free(ptr);
    return (new);
}
