/*
** main.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Thu Feb 04 23:26:39 2016 Adrien WERY
** Last update	Sat Feb 13 18:35:20 2016 Adrien WERY
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include "malloc.h"

int main()
{
    for (size_t i = 0; i < 1000000; i++) {
        malloc(1);
    }
    return (0);
}
