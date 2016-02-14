/*
** main.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Thu Feb 04 23:26:39 2016 Adrien WERY
** Last update	Wed Feb 10 23:17:03 2016 Adrien WERY
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include "malloc.h"

int main()
{
  int	i;

  i = 0;
  malloc(20000000);
  while (i < 1000000)
    {
      malloc(1);
      ++i;
    }
  /* malloc(1); */
  printf("end\n");
  return (0);
}
