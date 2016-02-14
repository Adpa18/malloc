/*
** free.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:29 2016 Adrien WERY
** Last update	Thu Feb 11 11:48:09 2016 Adrien WERY
*/

#include "malloc.h"

extern t_malloc *blocks;
extern pthread_mutex_t mutex;

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

void    mergeBlocks(t_block **block)
{
    if ((*block)->next && (*block)->next->isFree)
    {
        (*block)->size += B_SIZE((*block)->next->size);
        (*block)->next = (*block)->next->next;
        if ((*block)->next)
            (*block)->next->prev = (*block);
    }
    if ((*block)->prev && (*block)->prev->isFree)
    {
        (*block)->prev->size += B_SIZE((*block)->size);
        (*block)->prev->next = (*block)->next;
        if ((*block)->next)
            (*block)->next->prev = (*block)->prev;
        *block = (*block)->prev;
    }
}

void    _free(void *ptr)
{
    t_block *block;

    RETURN(!ptr || ptr > (void *)moreSpace(0, true));
    block = GET_BLOCK(ptr);
    RETURN(block->isFree);
    mergeBlocks(&block);
    block->isFree = true;
    if (block == block->parent->lastBlock)
    {
        block->parent->lastBlock = block->prev;
        block->parent->freeSize += B_SIZE(block->size);
        if (!block->parent->next && block->parent->freeSize > PAGE_SIZE)
        {
            if (blocks != block->parent)
            {
                if (block->parent->prev)
                    block->parent->prev->next = block->parent->next;
                brk(block->parent);
            }
        }
    }
    else
    if (block->parent->maxFreeSize < block->size)
        block->parent->maxFreeSize = block->size;
}

void    free(void *ptr)
{
    DEBUG(write(1, "free\n", 5));
    pthread_mutex_lock(&mutex);
    _free(ptr);
    pthread_mutex_unlock(&mutex);
    DEBUG(write(1, "freeE\n", 6));
}
