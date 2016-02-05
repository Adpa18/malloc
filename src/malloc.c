/*
** malloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:12:17 2016 Adrien WERY
** Last update	Fri Feb 05 23:11:09 2016 Adrien WERY
*/

#include "malloc.h"

t_malloc    *blocks = NULL;
size_t      pageSize = 0;

t_malloc    *getLastMalloc()
{
    t_malloc    *tmp;

    tmp = blocks;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

t_block     *addBlock(size_t size, t_block *block)
{
    block->size = size;
    block->isFree = false;
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
    mem->block = addBlock(size, (t_block *)((size_t)mem + MALLOC_SIZE));
    mem->lastBlock = mem->block;
    mem->next = NULL;
    return (mem);
}

void    *init(size_t size)
{
    pageSize = sysconf(_SC_PAGESIZE);
    return ((blocks = addMalloc(size)) ? GET_PTR(blocks->block) : NULL);
}

void    *malloc(size_t size)
{
    t_malloc    *tmp;

    if (size == 0)
        return (NULL);
    size = ALIGN(size, 8);
    if (pageSize == 0)
        return (init(size));
    tmp = blocks;
    while (tmp)
    {
        if (tmp->freeSize > REALSIZE(size))
        {
            tmp->lastBlock->next = addBlock(size, GET_NEXT_BLOCK(tmp->lastBlock));
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
