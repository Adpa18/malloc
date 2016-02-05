/*
** realloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:23 2016 Adrien WERY
** Last update	Fri Feb 05 20:30:54 2016 Adrien WERY
*/

#include "malloc.h"

void    *realloc(void *ptr, size_t size)
{
    void    *new;
    new = malloc(size + 1);
    if (!ptr)
        return (new);
    memcpy(new, ptr, ((t_block *)((size_t)ptr - BLOCK_SIZE))->size);
    free(ptr);
    return (new);
}
