/*
** realloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:23 2016 Adrien WERY
** Last update	Thu Feb 11 11:48:54 2016 Adrien WERY
*/

#include <string.h>
#include "malloc.h"

extern pthread_mutex_t mutex;

void    *_realloc(void *ptr, size_t size)
{
    t_block *block;
    void    *new;

    block = GET_BLOCK(ptr);
    R_NULL((size_t)ptr % ALIGN_SIZE != 0
    || (block->prev && ((size_t)block->prev % ALIGN_SIZE != 0
        || block->prev > block))
    || (block->next && ((size_t)block->next % ALIGN_SIZE != 0
        || block > block->next)));
    if (!block->next && (size < block->size
            || block->parent->freeSize >= size - block->size))
    {
        block->parent->freeSize = block->parent->freeSize + block->size - size;
        block->size = size;
        new = GET_PTR(block);
    }
    else
    {
        R_NULL(!(new = _malloc(size)));
        memcpy(new, ptr, MIN(block->size, size));
        _free(ptr);
    }
    return (new);
}

void    *realloc(void *ptr, size_t size)
{
    if (size == 0)
    {
        free(ptr);
        return (NULL);
    }
    DEBUG(write(1, "realloc\n", 8));
    size = ALIGN(size, ALIGN_SIZE);
    R_CUSTOM(!ptr, malloc(size));
    pthread_mutex_lock(&mutex);
    ptr = _realloc(ptr, size);
    pthread_mutex_unlock(&mutex);
    DEBUG(write(1, "reallocE\n", 9));
    return (ptr);
}
