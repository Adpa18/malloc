/*
** malloc.h for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:01 2016 Adrien WERY
** Last update	Mon Feb 08 15:41:46 2016 Adrien WERY
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <unistd.h>
#include <string.h>
// Dev
#include <stdio.h>
// Dev

// Merge close freeBlocks
// block->parent
// block->nextFree

#define MALLOC_SIZE sizeof(struct s_malloc)
#define BLOCK_SIZE  sizeof(struct s_block)
#define NB_PAGES    8

#define R_NULL(x) {if (x)return (NULL);}
#define R_CUSTOM(x, c) {if (x)return (c);}
#define RETURN(x) {if (x)return;}
#define REALSIZE(size) ((size_t)size + BLOCK_SIZE)
#define GET_PTR(block) ((void*)(REALSIZE(block)))
#define GET_BLOCK(ptr) ((t_block *)((size_t)ptr - BLOCK_SIZE))
#define GET_NEXT_BLOCK(block) ((t_block*)(REALSIZE(block) + block->size))
#define ALIGN(size, pageSize) ((size + pageSize - 1) &~ (pageSize - 1))

typedef __SIZE_TYPE__ size_t;
typedef enum { false, true } bool;

typedef struct      s_block {
    size_t          size;
    bool            isFree;
    struct s_malloc *parent;
    struct s_block  *nextFree;
    struct s_block  *next;
}                   t_block;

typedef struct      s_malloc {
    size_t          freeSize;
    t_block         *block;
    t_block         *lastBlock;
    struct s_malloc *next;
}                   t_malloc;

void    *malloc(size_t size);
void    *calloc(size_t nb, size_t size);
void    *realloc(void *ptr, size_t size);
void    free(void *ptr);
void    show_alloc_mem();
#endif /* !MALLOC_H_ */
