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
  bool	many;

  i = 0;
  ret = 0;
  g_prog_name = argv[0];
  many = false;
  if (argc == 1)
    {
      if (my_nm("a.out", false) == 1)
	ret = 1;
    }
  if (argc > 2)
    many = true;
  while (++i < argc)
    {
      if (my_nm(argv[i], many) == 1)
	ret = 1;
    }
  return (ret);
}
