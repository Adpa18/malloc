/*
** malloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:12:17 2016 Adrien WERY
** Last update	Wed Feb 10 17:01:53 2016 Adrien WERY
*/

#include "malloc.h"

t_malloc    *blocks = NULL;
t_malloc    *last = NULL;
t_block     *freeBlocks = NULL;
pthread_mutex_t mutexM = PTHREAD_MUTEX_INITIALIZER;
// size_t      pageSize = 0;

t_block     *addBlock(const size_t size, t_block *block, t_malloc *parent)
{
    block->size = size;
    block->isFree = false;
    block->parent = parent;
    block->nextFree = NULL;
    block->prev = parent->lastBlock;
    block->next = NULL;
    parent->lastBlock = block;
    return (block);
}

void    *checkInFree(const size_t size)
{
    t_block *tmp;
    t_block *block;

    R_NULL(!(tmp = freeBlocks));
    if (tmp && tmp->size >= size && tmp->isFree)
        {
            freeBlocks = tmp->nextFree;
            tmp->isFree = false;
            tmp->nextFree = NULL;
            return(GET_PTR(tmp));
        }
    while (tmp && tmp->nextFree)
    {
        if (tmp->nextFree->size >= size && tmp->nextFree->isFree)
        {
            block = tmp->nextFree;
            tmp->nextFree = tmp->nextFree->nextFree;
            block->isFree = false;
            block->nextFree = NULL;
            return (GET_PTR(block));
        }
        tmp = tmp->nextFree;
    }
    return (NULL);
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
        tmp = tmp->next;
    }
    return (NULL);
}

t_malloc    *moreSpace(const size_t size)
{
    t_malloc    *mem;
    size_t      memSize;

    memSize = ALIGN(REALSIZE(size) + MALLOC_SIZE, PAGE_SIZE);
    R_NULL((mem = sbrk(memSize)) == (void *) -1);
    mem->freeSize = memSize - REALSIZE(size) - MALLOC_SIZE;
    mem->startBlock = addBlock(size, (t_block *)((size_t)mem + MALLOC_SIZE), mem);
    mem->next = NULL;
    if (last)
    {
        blocks = mem;
        last->next = mem;
    }
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
    IF_SET(!ptr && freeBlocks, ptr = checkInFree(size));
    IF_SET(!ptr && blocks, ptr = findSpace(blocks, size));
    IF_SET(!ptr, ptr = moreSpace(size));
    pthread_mutex_unlock(&mutexM);
    DEBUG(write(1, "mallocE\n", 8));
    return (ptr);
}
