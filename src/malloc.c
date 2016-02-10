/*
** malloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:12:17 2016 Adrien WERY
** Last update	Wed Feb 10 23:32:21 2016 Adrien WERY
*/

#include "malloc.h"

t_malloc    *blocks = NULL;
pthread_mutex_t mutexM = PTHREAD_MUTEX_INITIALIZER;

t_block     *addBlock(const size_t size, t_block *block, t_malloc *parent)
{
    block->size = size;
    block->isFree = false;
    block->parent = parent;
    block->prev = parent->lastBlock;
    block->next = NULL;
    parent->lastBlock = block;
    return (block);
}

void    *getFreeBlock(t_block *tmp, size_t size, size_t *max)
{
    void    *ptr;

    *max = 0;
    ptr = NULL;
    while (tmp->next)
    {
        if (tmp->isFree && tmp->size >= size)
        {
            tmp->isFree = false;
            ptr = GET_PTR(tmp);
        }
        else if (tmp->size > *max)
            *max = tmp->size;
        tmp = tmp->next;
    }
    return (ptr);
}

void    *findSpace(t_malloc *tmp, const size_t size)
{
    while (tmp)
    {
        if (tmp->freeSize > REALSIZE(size))
        {
            if (!tmp->lastBlock)
                tmp->startBlock = addBlock(size, (t_block *)((size_t)tmp + MALLOC_SIZE), tmp);
            else
                tmp->lastBlock->next = addBlock(size, GET_NEXT_BLOCK(tmp->lastBlock), tmp);
            tmp->freeSize -= MAX(REALSIZE(size), 0);
            return (GET_PTR(tmp->lastBlock));
        }
        else if (tmp->maxFreeSize > size)
            return (getFreeBlock(tmp->startBlock, size, &(tmp->maxFreeSize)));
        tmp = tmp->next;
    }
    return (NULL);
}

t_malloc    *moreSpace(const size_t size)
{
    static t_malloc     *last = NULL;
    t_malloc    *mem;
    size_t      memSize;

    memSize = ALIGN(REALSIZE(size) + MALLOC_SIZE, PAGE_SIZE);
    R_NULL((mem = sbrk(memSize)) == (void *) -1);
    mem->freeSize = memSize - REALSIZE(size) - MALLOC_SIZE;
    mem->maxFreeSize = 0;
    mem->startBlock = addBlock(size, (t_block *)((size_t)mem + MALLOC_SIZE), mem);
    mem->next = NULL;
    mem->prev = last;
    if (!blocks)
        blocks = mem;
    if (last)
        last->next = mem;
    last = mem;
    return (GET_PTR(mem->startBlock));
}

void    *malloc(size_t size)
{
    void        *ptr;

    R_NULL(size == 0);
    size = ALIGN(size, ALIGN_SIZE);
    ptr = NULL;
    pthread_mutex_lock(&mutexM);
    DEBUG(write(1, "malloc\n", 7));
    IF_SET(!ptr && blocks, ptr = findSpace(blocks, size));
    IF_SET(!ptr, ptr = moreSpace(size));
    pthread_mutex_unlock(&mutexM);
    DEBUG(write(1, "mallocE\n", 8));
    return (ptr);
}
