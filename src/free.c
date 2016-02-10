/*
** free.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:29 2016 Adrien WERY
** Last update	Wed Feb 10 17:00:06 2016 Adrien WERY
*/

#include "malloc.h"

extern t_block  *freeBlocks;
extern pthread_mutex_t mutexM;

void    mergeLinks(t_block **block)
{
    if ((*block)->nextFree)
        (*block)->nextFree->prevFree = (*block)->prevFree;
    if ((*block)->prevFree)
        (*block)->prevFree->nextFree = (*block)->nextFree;
    (*block)->nextFree = NULL;
    (*block)->prevFree = NULL;
}

void    mergeBlocks(t_block **block)
{
    // if ((*block)->prev && (*block)->prev->isFree)
    // {
    //     (*block)->prev->size += REALSIZE((*block)->size);
    //     (*block)->prev->next = (*block)->next;
    //     if ((*block)->next)
    //         (*block)->next->prev = (*block)->prev;
    //     (*block) = (*block)->prev;
    //     mergeLinks(block);
    // }
    if ((*block)->next && (*block)->next->isFree)
    {
        (*block)->size += REALSIZE((*block)->next->size);
        (*block)->next = (*block)->next->next;
        if ((*block)->next)
            mergeLinks(&((*block)->next));
    }
}

void    free(void *ptr)
{
    t_block *block;
    t_block    *tmp;

    RETURN(!ptr);
    block = GET_BLOCK(ptr);
    RETURN(block->isFree);
    pthread_mutex_lock(&mutexM);
    DEBUG(write(1, "free\n", 5));
    // mergeBlocks(&block);
    block->isFree = true;
    if (block == block->parent->lastBlock)
    {
        block->parent->lastBlock = block->prev;
        block->parent->freeSize += REALSIZE(block->size);
    }
    else if (!(tmp = freeBlocks))
        freeBlocks = block;
    else
    {
        while (tmp->nextFree)
            tmp = tmp->nextFree;
        tmp->nextFree = block;
        block->prevFree = tmp;
    }
    pthread_mutex_unlock(&mutexM);
    DEBUG(write(1, "freeE\n", 6));
}
