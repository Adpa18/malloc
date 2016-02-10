/*
** realloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:23 2016 Adrien WERY
** Last update	Wed Feb 10 19:31:21 2016 Adrien WERY
*/

#include <string.h>
#include "malloc.h"

pthread_mutex_t mutexR = PTHREAD_MUTEX_INITIALIZER;

size_t nb = 0;

void    *realloc(void *ptr, size_t size)
{
    t_block *block;
    void    *new;

    if (size == 0)
    {
        free(ptr);
        return (NULL);
    }
    size = ALIGN(size, ALIGN_SIZE);
    DEBUG(write(1, "realloc\n", 8));
    R_CUSTOM(!ptr, malloc(size));
    pthread_mutex_lock(&mutexR);
    block = GET_BLOCK(ptr);
    R_NULL((size_t)ptr % ALIGN_SIZE != 0
    || (block->prev && ((size_t)block->prev % ALIGN_SIZE != 0 || block->prev > block))
    || (block->next && ((size_t)block->next % ALIGN_SIZE != 0 || block > block->next)));
    if (!block->next && (size < block->size || block->parent->freeSize >= size - block->size))
    {
        block->parent->freeSize = block->parent->freeSize + block->size - size;
        block->size = size;
        new = GET_PTR(block);
    }
    else
    {
        R_NULL(!(new = malloc(size)));
        memcpy(new, ptr, MIN(block->size, size));
        free(ptr);
    }
    pthread_mutex_unlock(&mutexR);
    DEBUG(write(1, "reallocE\n", 9));
    return (new);
}
