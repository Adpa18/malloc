/*
** malloc.h for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:01 2016 Adrien WERY
** Last update	Sat Feb 13 20:47:12 2016 Adrien WERY
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <unistd.h>
#include <pthread.h>
// Dev
#include <stdio.h>
#define D false
#define DEBUG(x) {if (D){x;}}
// Dev

#if __x86_64__
    #define ALIGN_SIZE 8
#else
    #define ALIGN_SIZE 4
#endif

typedef __SIZE_TYPE__ size_t;
typedef enum { false, true } bool;

#define MALLOC_SIZE sizeof(struct s_malloc)
#define BLOCK_SIZE  sizeof(struct s_block)
#define NB_PAGES    2
#define PAGE_SIZE   (size_t)(sysconf(_SC_PAGESIZE) * NB_PAGES)

#define R_NULL(x) {if (x)return (NULL);}
#define R_FALSE(x) {if (x)return (false);}
#define R_CUSTOM(x, c) {if (x)return (c);}
#define IF_SET(x, c) {if (x)c;}
#define RETURN(x) {if (x)return;}
#define M_SIZE(ptr) ((size_t)ptr + MALLOC_SIZE)
#define B_SIZE(ptr) ((size_t)ptr + BLOCK_SIZE)
#define GET_PTR(block) ((void*)(B_SIZE(block)))
#define GET_BLOCK(ptr) ((t_block *)((size_t)ptr - BLOCK_SIZE))
#define GET_NEXT_BLOCK(block) ((t_block*)(B_SIZE(block) + block->size))
#define FIRST_PTR() ((void*)B_SIZE(blocks->startBlock))
#define LAST_PTR() ((void*)B_SIZE(last->lastBlock))
#define VALID_PTR(ptr) (ptr > FIRST_PTR() && ptr < LAST_PTR())
#define ALIGN(size, pageSize) ((size + pageSize - 1) &~ (pageSize - 1))
#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x < y) ? x : y)

typedef struct      s_block {
    size_t          size;
    bool            isFree;
    struct s_malloc *parent;
    struct s_block  *prev;
    struct s_block  *next;
}                   t_block;

typedef struct      s_malloc {
    size_t          freeSize;
    size_t          maxFreeSize;
    t_block         *startBlock;
    t_block         *lastBlock;
    struct s_malloc *prev;
    struct s_malloc *next;
}                   t_malloc;

void    *_malloc(size_t size);
void    _free(void *ptr);
void    *getFreeBlock(t_block *tmp, size_t size, size_t *max);

void    *malloc(size_t size);
void    *calloc(size_t nb, size_t size);
void    *realloc(void *ptr, size_t size);
void    free(void *ptr);
void    show_alloc_mem();

#endif /* !MALLOC_H_ */
