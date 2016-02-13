/*
** show.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:37 2016 Adrien WERY
** Last update	Sat Feb 13 16:22:16 2016 Adrien WERY
*/

#include "malloc.h"

extern t_malloc    *blocks;

void    show_alloc_mem()
{
    t_malloc    *tmp;
    t_block     *tmp2;

    tmp = blocks;
    printf("break : 0x%lX\n", (size_t) sbrk(0));
    while (tmp)
    {
        tmp2 = tmp->startBlock;
        while (tmp2)
        {
            if (!tmp2->isFree)
            {
                printf("0x%lX - 0x%lX : %lu bytes\n",
                B_SIZE(tmp2), (size_t)GET_NEXT_BLOCK(tmp2), tmp2->size);
            }
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }
}
