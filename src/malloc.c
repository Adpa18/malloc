/*
** malloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:12:17 2016 Adrien WERY
** Last update	Tue Feb 09 11:09:07 2016 Adrien WERY
*/

#include "malloc.h"

t_malloc    *blocks = NULL;
t_block     *freeBlocks = NULL;
size_t      pageSize = 0;
pthread_mutex_t mutexM = PTHREAD_MUTEX_INITIALIZER;

t_malloc    *getLastMalloc()
{
    t_malloc    *tmp;

    tmp = blocks;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

t_block     *addBlock(size_t size, t_block *block, t_malloc *parent)
{
    block->size = size;
    block->isFree = false;
    block->parent = parent;
    block->nextFree = NULL;
    block->next = NULL;
    return (block);
}

t_malloc    *addMalloc(size_t size)
{
    t_malloc    *mem;
    size_t      memSize;

    memSize = ALIGN(REALSIZE(size) + MALLOC_SIZE, pageSize);
    R_NULL((mem = sbrk(memSize)) == (void *) -1);
    mem->freeSize = memSize - REALSIZE(size) - MALLOC_SIZE;
    mem->block = addBlock(size, (t_block *)((size_t)mem + MALLOC_SIZE), mem);
    mem->lastBlock = mem->block;
    mem->next = NULL;
    return (mem);
}

void    *checkInFree(size_t size)
{
    t_block *tmp;
    t_block *block;

    tmp = freeBlocks;
    // if (tmp && tmp->size >= size && tmp->isFree)
    //     {
    //         freeBlocks = tmp->nextFree;
    //         tmp->isFree = false;
    //         tmp->nextFree = NULL;
    //         return (GET_PTR(tmp));
    //     }
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

void    *findSpace(t_malloc *tmp, size_t size)
{
    while (tmp)
    {
        if (tmp->freeSize > REALSIZE(size))
        {
            if (tmp->block)
            {
                tmp->lastBlock->next = addBlock(size, GET_NEXT_BLOCK(tmp->lastBlock), tmp);
                tmp->lastBlock = tmp->lastBlock->next;
            }
            else
            {
                tmp->block = addBlock(size, (t_block *)((size_t)tmp + MALLOC_SIZE), tmp);
                tmp->lastBlock = tmp->block;
            }
            tmp->freeSize -= (REALSIZE(size) > tmp->freeSize) ? 0 : REALSIZE(size);
            return (GET_PTR(tmp->lastBlock));
        }
        tmp = tmp->next;
    }
    return (NULL);
}

void    *moreSpace(size_t size)
{
    t_malloc    *tmp;

    tmp = getLastMalloc();
    tmp->next = addMalloc(size);
    return (GET_PTR(tmp->next->block));
}

void    *init(size_t size)
{
    pageSize = sysconf(_SC_PAGESIZE);
    return ((blocks = addMalloc(size)) ? GET_PTR(blocks->block) : NULL);
}

void    *malloc(size_t size)
{
    void        *ptr;

    R_NULL(size == 0);
    size = ALIGN(size, 8);
    ptr = NULL;
    pthread_mutex_lock(&mutexM);
    DEBUG(write(1, "malloc\n", 7));
    IF_SET(pageSize == 0, ptr = init(size));
    IF_SET(!ptr, ptr = checkInFree(size));
    IF_SET(!ptr, ptr = findSpace(blocks, size));
    IF_SET(!ptr, ptr = moreSpace(size));
    pthread_mutex_unlock(&mutexM);
    DEBUG(write(1, "mallocE\n", 8));
    return (ptr);
}
