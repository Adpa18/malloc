/*
** free.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:29 2016 Adrien WERY
** Last update	Sat Feb 06 16:23:48 2016 Adrien WERY
*/

#include "malloc.h"

extern t_block  *freeBlocks;

void    free(void *ptr)
{
    t_block *block;
    t_block    *tmp;

    if (!ptr)
        return;
    write(1, "free\n", 5);
    block = GET_BLOCK(ptr);
    if (block->isFree)
        return;
    block->isFree = true;
    if (!block->next)
    {
        write(1, "rm\n", 3);
        if ((tmp = block->parent->block) != block->parent->lastBlock)
            {
                while (tmp->next != block->parent->lastBlock)
                    tmp = tmp->next;
            }
        block->parent->lastBlock = tmp;
        block->parent->lastBlock->next = NULL;
        block->parent->freeSize += REALSIZE(block->size);
        return;
    }
    if (!(tmp = freeBlocks))
        {
            freeBlocks = block;
            return;
        }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = block;
}
