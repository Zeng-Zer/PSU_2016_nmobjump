/*
** utils.c for utils in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon Feb 13 13:06:06 2017 David Zeng
** Last update Mon Feb 13 13:06:06 2017 David Zeng
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_objdump.h"

int	file_truncated(char const *filename)
{
  fprintf(stderr, "%s: %s: File truncated\n", g_prog_name, filename);
  return (1);
}

bool	only_whitespace(char const *str, int size)
{
  int	i;

  i = -1;
  while (++i < size)
    {
      if (str[i] != ' ')
	return (false);
    }
  return (true);
}
