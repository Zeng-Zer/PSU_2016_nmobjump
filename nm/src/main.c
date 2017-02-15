/*
** main.c for main in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon Jan 23 17:57:49 2017 David Zeng
** Last update Mon Jan 23 17:57:49 2017 David Zeng
*/

#include "my_nm.h"

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
      if (my_nm("a.out") == 1)
	ret = 1;
    }
  while (++i < argc)
    {
      if (my_nm(argv[i]) == 1)
	ret = 1;
    }
  return (ret);
}
