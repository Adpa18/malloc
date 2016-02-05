/*
** malloc.h for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:01 2016 Adrien WERY
** Last update	Fri Feb 05 15:27:32 2016 Adrien WERY
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <unistd.h>
// Dev
#include <stdio.h>
// Dev

#define DEFAULT_SIZE  4096
#define MALLOC_SIZE sizeof(struct s_malloc)
#define BLOCK_SIZE sizeof(struct s_block)

#define MAX(x, y) (x > y) ? x : y

typedef __SIZE_TYPE__ size_t;
typedef enum { false, true } bool;

typedef struct      s_block {
    size_t          size;
    bool            isFree;
    void            *ptr;
    struct s_block  *next;
}                   t_block;

typedef struct      s_malloc {
    size_t          size;
    size_t          freeSize;
    void            *lastPtr;
    t_block         *block;
    struct s_malloc *next;
}                   t_malloc;

void    *malloc(size_t size);
void    *calloc(size_t nb, size_t size);
void    *realloc(void *ptr, size_t size);
void    free(void *ptr);
void    show_alloc_mem();
#endif /* !MALLOC_H_ */
