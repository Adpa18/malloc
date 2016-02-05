/*
** malloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:12:17 2016 Adrien WERY
** Last update	Fri Feb 05 01:02:39 2016 Adrien WERY
*/

#include "malloc.h"

t_malloc    *blocks = NULL;

t_malloc    *getLastMalloc()
{
    t_malloc    *tmp;

    tmp = blocks;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

t_block     *getLastBlock(t_malloc *mem)
{
    t_block *tmp;

    tmp = mem->block;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

t_block     *addBlock(size_t size, void *ptr)
{
    t_block *block;

    block = ptr;
    (void)size;
    // SegFault on
    // block->size = size;
    block->isFree = false;
    block->ptr = ptr + BLOCK_SIZE;
    block->next = NULL;
    return (block);
}

t_malloc    *addMalloc(size_t size)
{
    t_malloc    *mem;
    size_t  memSize;

    memSize = MAX(size, DEFAULT_SIZE);
    mem = sbrk(MALLOC_SIZE + memSize);
    mem->size = memSize;
    mem->freeSize = memSize - size;
    mem->block = addBlock(size, &mem + MALLOC_SIZE);
    mem->lastPtr = mem->block + size;
    mem->next = NULL;
    return (mem);
}

void    *malloc(size_t size)
{
    if (size == 0)
        return (NULL);
    if (!blocks && !(blocks = addMalloc(size)))
        return (NULL);
    // for on all mallocs

    // SegDault on printing
    // printf("%lu\n", blocks->freeSize);
    // printf("%d\n", blocks->freeSize > size);
    // return (NULL);
    if (blocks->freeSize > size)
    {
        t_block *last = getLastBlock(blocks);
        last->next = addBlock(size, blocks->lastPtr);
        return (last->next->ptr);
    }
    t_malloc    *last = getLastMalloc();
    last->next = addMalloc(size);
    return (last->next->block->ptr);
}
