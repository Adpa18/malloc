/*
** free.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:29 2016 Adrien WERY
** Last update	Fri Feb 05 22:52:10 2016 Adrien WERY
*/

#include "malloc.h"

void    free(void *ptr)
{
    t_block *block;

    block = (t_block *)((size_t)ptr - BLOCK_SIZE);
    block->isFree = true;
}
