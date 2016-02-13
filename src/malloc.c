/*
** malloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:12:17 2016 Adrien WERY
** Last update	Sat Feb 13 18:31:06 2016 Adrien WERY
*/

#include "malloc.h"

t_malloc    *blocks = NULL;
t_malloc     *last = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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

void    *findSpace(t_malloc *tmp, const size_t size)
{
    while (tmp)
    {
        if (tmp->freeSize > B_SIZE(size))
        {
            if (!tmp->lastBlock)
                tmp->startBlock = addBlock(size, (t_block *)M_SIZE(tmp), tmp);
            else
                tmp->lastBlock->next = addBlock(size,
                    GET_NEXT_BLOCK(tmp->lastBlock), tmp);
            tmp->freeSize -= MAX(B_SIZE(size), 0);
            return (GET_PTR(tmp->lastBlock));
        }
        else if (tmp->maxFreeSize >= size)
            return (getFreeBlock(tmp->startBlock, size, &(tmp->maxFreeSize)));
        tmp = tmp->next;
    }
    return (NULL);
}

t_malloc    *moreSpace(const size_t size)
{
    t_malloc    *mem;
    size_t      memSize;

    memSize = ALIGN(M_SIZE(B_SIZE(size)), PAGE_SIZE);
    R_NULL((mem = sbrk(memSize)) == (void *) -1);
    mem->freeSize = memSize - B_SIZE(size) - MALLOC_SIZE;
    mem->maxFreeSize = 0;
    mem->startBlock = addBlock(size, (t_block *)M_SIZE(mem), mem);
    mem->next = NULL;
    mem->prev = last;
    if (last)
        last->next = mem;
    else
      blocks = mem;
    last = mem;
    return (GET_PTR(mem->startBlock));
}

void    *_malloc(size_t size)
{
    void        *ptr;

    ptr = NULL;
    IF_SET(!ptr && blocks, ptr = findSpace(blocks, size));
    IF_SET(!ptr, ptr = moreSpace(size));
    return (ptr);
}

void    *malloc(size_t size)
{
    void    *ptr;

    size = ALIGN(size, ALIGN_SIZE);
    DEBUG(write(1, "malloc\n", 7));
    pthread_mutex_lock(&mutex);
    ptr = _malloc(size);
    pthread_mutex_unlock(&mutex);
    DEBUG(write(1, "mallocE\n", 8));
    return (ptr);
}
