/*
** realloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:23 2016 Adrien WERY
** Last update	Sat Feb 06 16:03:38 2016 Adrien WERY
*/

#include "malloc.h"

void    *realloc(void *ptr, size_t size)
{
    t_block *block;
    void    *new;

    ISNULL(size);
    if (!ptr)
        return (malloc(size + 1));
    block = GET_BLOCK(ptr);
    if (!block->next && block->parent->freeSize >= size - block->size)
    {
        block->parent->freeSize -= size - block->size;
        block->size = size;
        return (GET_PTR(block));
    }
    if (!(new = malloc(size + 1)))
        return (NULL);
    memcpy(new, ptr, GET_BLOCK(ptr)->size);
    // free(ptr);
    return (new);
}
