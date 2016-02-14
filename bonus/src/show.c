/*
** show.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:37 2016 Adrien WERY
** Last update	Thu Feb 11 11:36:29 2016 Adrien WERY
*/

#include "malloc.h"

extern t_malloc    *blocks;

void    show_alloc_mem()
{
    t_block *tmp;

    tmp = blocks->startBlock;
    printf("break : 0x%lX\n", (size_t) sbrk(0));
    while (tmp)
    {
        if (!tmp->isFree)
        {
            printf("0x%lX - 0x%lX : %lu bytes\n",
            B_SIZE(tmp), (size_t)GET_NEXT_BLOCK(tmp), tmp->size);
        }
    }
}
