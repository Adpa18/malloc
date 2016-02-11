/*
** free.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:29 2016 Adrien WERY
** Last update	Thu Feb 11 05:26:07 2016 Adrien WERY
*/

#include "malloc.h"

extern t_malloc *blocks;
extern pthread_mutex_t mutexM;

void    mergeBlocks(t_block **block)
{
    if ((*block)->next && (*block)->next->isFree)
    {
        (*block)->size += REALSIZE((*block)->next->size);
        (*block)->next = (*block)->next->next;
        if ((*block)->next)
            (*block)->next->prev = (*block);
    }
    if ((*block)->prev && (*block)->prev->isFree)
    {
        (*block)->prev->size += REALSIZE((*block)->size);
        (*block)->prev->next = (*block)->next;
        if ((*block)->next)
            (*block)->next->prev = (*block)->prev;
        *block = (*block)->prev;
    }
}

void    free(void *ptr)
{
    t_block *block;

    RETURN(!ptr || ptr > (void *)moreSpace(0, true));
    block = GET_BLOCK(ptr);
    RETURN(block->isFree);
    pthread_mutex_lock(&mutexM);
    DEBUG(write(1, "free\n", 5));
    mergeBlocks(&block);
    block->isFree = true;
    if (block == block->parent->lastBlock)
    {
        block->parent->lastBlock = block->prev;
        block->parent->freeSize += REALSIZE(block->size);
        if (!block->parent->next && block->parent->freeSize > PAGE_SIZE)
        {
            if (blocks != block->parent)
            {
                if (block->parent->prev)
                    block->parent->prev->next = block->parent->next;
                brk(block->parent);
                // sbrk(-(block->parent->freeSize + MALLOC_SIZE));
            }
        }
    }
    else
    if (block->parent->maxFreeSize < block->size)
        block->parent->maxFreeSize = block->size;
    pthread_mutex_unlock(&mutexM);
    DEBUG(write(1, "freeE\n", 6));
}
