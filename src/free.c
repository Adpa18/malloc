/*
** free.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:29 2016 Adrien WERY
** Last update	Sat Feb 06 16:01:57 2016 Adrien WERY
*/

#include "malloc.h"

extern t_block  *freeBlocks;

void    free(void *ptr)
{
    t_block *block;
    t_block    *tmp;

    block = GET_BLOCK(ptr);
    block->isFree = true;
    if (!block->next)
    {
        // if (!block->parent->block)
        //     printf("%p\n", block->parent->block);
        // block->parent->block == NULL
        if ((tmp = block->parent->block) != block->parent->lastBlock)
            {
                while (tmp->next != block->parent->lastBlock)
                    tmp = tmp->next;
            }
        // if (tmp)
        // {
        //     tmp = block;
        //     block->parent->block = tmp;
        // }
        block->parent->lastBlock = tmp;
        block->parent->lastBlock->next = NULL;
        block->parent->freeSize += REALSIZE(block->size);
    }
    else
    {
        if (!(tmp = freeBlocks))
            {
                freeBlocks = block;
                return;
            }
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = block;
    }
}
