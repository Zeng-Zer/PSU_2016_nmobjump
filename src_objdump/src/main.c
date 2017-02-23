/*
** main.c for main in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon Jan 23 17:57:49 2017 David Zeng
** Last update Mon Jan 23 17:57:49 2017 David Zeng
*/

#include <stdio.h>
#include "my_objdump.h"

char	*g_prog_name;

int	main(int argc, char *argv[])
{
  int	i;
  int	ret;

  i = 0;
  ret = 0;
  g_prog_name = argv[0];
  if (argc == 1)
    {
      if (my_objdump("a.out") == 1)
	ret = 1;
    }
  while (++i < argc)
    {
      if (my_objdump(argv[i]) == 1)
	ret = 1;
    }
  return (ret);
}
