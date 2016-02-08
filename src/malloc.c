/*
** malloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:12:17 2016 Adrien WERY
** Last update	Mon Feb 08 16:03:11 2016 Adrien WERY
*/

#include "malloc.h"

t_malloc    *blocks = NULL;
t_block     *freeBlocks = NULL;
size_t      pageSize = 0;

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
    size_t  memSize;

    memSize = ALIGN(size + MALLOC_SIZE, pageSize);
    if ((mem = sbrk(memSize)) == (void *) -1)
        return (NULL);
    mem->freeSize = memSize - REALSIZE(size) - MALLOC_SIZE;
    mem->block = addBlock(size, (t_block *)((size_t)mem + MALLOC_SIZE), mem);
    mem->lastBlock = mem->block;
    mem->next = NULL;
    return (mem);
}

void    *checkInFree(size_t size)
{
    t_block *tmp;

    tmp = freeBlocks;
    while (tmp && tmp->nextFree)
    {
        R_CUSTOM(tmp->size >= size, GET_PTR(tmp));
        tmp = tmp->nextFree;
    }
    return (NULL);
}

void    *init(size_t size)
{
    pageSize = sysconf(_SC_PAGESIZE);
    return ((blocks = addMalloc(size)) ? GET_PTR(blocks->block) : NULL);
}

void    *malloc(size_t size)
{
    t_malloc    *tmp;
    void        *ptr;

    R_NULL(size == 0);
    size = ALIGN(size, 8);
    R_CUSTOM(pageSize == 0, init(size));
    R_CUSTOM((ptr = checkInFree(size)), ptr);
    tmp = blocks;
    while (tmp)
    {
        if (tmp->freeSize > REALSIZE(size))
        {
            tmp->lastBlock->next = addBlock(size, GET_NEXT_BLOCK(tmp->lastBlock), tmp);
            tmp->lastBlock = tmp->lastBlock->next;
            tmp->freeSize -= (REALSIZE(size) > tmp->freeSize) ? 0 : REALSIZE(size);
            return (GET_PTR(tmp->lastBlock));
        }
        tmp = tmp->next;
    }
    tmp = getLastMalloc();
    tmp->next = addMalloc(size);
    return (GET_PTR(tmp->next->block));
}
