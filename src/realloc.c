/*
** realloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:23 2016 Adrien WERY
** Last update	Tue Feb 09 12:38:08 2016 Adrien WERY
*/

#include <string.h>
#include "malloc.h"

pthread_mutex_t mutexR = PTHREAD_MUTEX_INITIALIZER;

void    *realloc(void *ptr, size_t size)
{
    t_block *block;
    void    *new;

    R_NULL(size == 0);
    DEBUG(write(1, "realloc\n", 8));
    R_CUSTOM(!ptr, malloc(size + 1));
    pthread_mutex_lock(&mutexR);
    block = GET_BLOCK(ptr);
    if (!block->next && (size < block->size || block->parent->freeSize >= size - block->size))
    {
        block->parent->freeSize = block->parent->freeSize + block->size - size;
        block->size = size;
        new = GET_PTR(block);
    }
    else
    {
        R_NULL(!(new = malloc(size + 1)));
        memcpy(new, ptr, MIN(block->size, size));
        free(ptr);
    }
    pthread_mutex_unlock(&mutexR);
    DEBUG(write(1, "reallocE\n", 9));
    return (new);
}
