/*
** malloc.h for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 01 15:13:01 2016 Adrien WERY
** Last update	Mon Feb 01 15:18:18 2016 Adrien WERY
*/

#ifndef MALLOC_H_
#define MALLOC_H_

typedef __SIZE_TYPE__ size_t;

void    *malloc(size_t size);
void    *calloc(size_t nb, size_t size);
void    *realloc(void *ptr, size_t size);
void    free(void *ptr);
void    show_alloc_mem();
#endif /* !MALLOC_H_ */
