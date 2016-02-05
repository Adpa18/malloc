/*
** main.c for PSU_2015_malloc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Thu Feb 04 23:26:39 2016 Adrien WERY
** Last update	Fri Feb 05 16:41:05 2016 Adrien WERY
*/

#include <stdlib.h>
#include <stdio.h>

int main()
{
  char *toto;
  int	*nbs;
  int i = 0;

  toto = (char *)malloc(sizeof(char) * 4);
  toto[0] = 'h';
  toto[1] = 'e';
  toto[2] = 'y';
  toto[3] = 0;
  printf("%s\n", toto);

  nbs = (int *)malloc(sizeof(int) * 3);
  nbs[0] = 0;
  nbs[1] = 1;
  nbs[2] = 2;

  printf("%d\n%d\n%d\n", nbs[0], nbs[1], nbs[2]);

  while (i < 1000)
    {
      malloc(1);
      ++i;
    }
  free(toto);
  printf("%s\n", toto);
  return (0);
}
