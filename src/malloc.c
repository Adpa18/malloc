/*
** malloc.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:12:17 2016 Adrien WERY
** Last update	Fri Feb 05 16:11:05 2016 Adrien WERY
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

t_block     *getLastBlock(t_malloc *mem)
{
    t_block *tmp;

    tmp = mem->block;
    while (tmp->next)
    {
        // write(1, "cc\n", 3);
        tmp = tmp->next;
    }
    return (tmp);
}

t_block     *addBlock(size_t size, void *ptr)
{
    t_block *block;

    block = ptr;
    block->size = size;
    block->isFree = false;
    block->ptr = ptr + BLOCK_SIZE;
    block->next = NULL;
    return (block);
}

t_malloc    *addMalloc(size_t size)
{
    t_malloc    *mem;
    size_t  memSize;

    memSize = MAX(size, pageSize);
    mem = sbrk(MALLOC_SIZE + memSize);
    mem->size = memSize;
    mem->freeSize = memSize - size;
    mem->block = addBlock(size, &mem + MALLOC_SIZE);
    mem->next = NULL;
    return (mem);
}

void    *malloc(size_t size)
{
    if (size == 0)
    return (NULL);
    if (pageSize == 0)
        pageSize = sysconf(_SC_PAGESIZE);
    if (!blocks)
        return ((blocks = addMalloc(size)) ? blocks->block->ptr : NULL);
    // for on all mallocs
    if (blocks->freeSize > size)
    {
        t_block *last = getLastBlock(blocks);
        last->next = addBlock(size, (void *)(last->ptr + last->size));
        blocks->freeSize -= size;
        return (last->next->ptr);
    }
    t_malloc    *last = getLastMalloc();
    last->next = addMalloc(size);
    return (last->next->block->ptr);
}
