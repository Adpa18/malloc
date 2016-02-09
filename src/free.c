/*
** free.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:29 2016 Adrien WERY
** Last update	Tue Feb 09 11:33:24 2016 Adrien WERY
*/

#include "malloc.h"

extern t_block  *freeBlocks;
extern pthread_mutex_t mutexM;

void    mergeBlocks(t_malloc *parent)
{
    t_block *tmp;

    tmp = parent->block;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
}

void    free(void *ptr)
{
    t_block *block;
    t_block    *tmp;

    RETURN(!ptr);
    block = GET_BLOCK(ptr);
    RETURN(block->isFree);
    block->isFree = true;
    pthread_mutex_lock(&mutexM);
    DEBUG(write(1, "free\n", 5));
    // if (!block->next)
    // {
    //     if ((tmp = block->parent->block) != block->parent->lastBlock)
    //         while (tmp->next != block->parent->lastBlock)
    //             tmp = tmp->next;
    //     block->parent->lastBlock = tmp;
    //     block->parent->lastBlock->next = NULL;
    //     block->parent->freeSize += REALSIZE(block->size);
    // }
    // else
    if (!(tmp = freeBlocks))
        freeBlocks = block;
    else
    {
        while (tmp->nextFree)
            tmp = tmp->nextFree;
        tmp->nextFree = block;
        tmp->nextFree->nextFree = NULL;
    }
    pthread_mutex_unlock(&mutexM);
    DEBUG(write(1, "freeE\n", 6));
}
