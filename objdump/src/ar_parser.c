/*
** ar_parser.c for ar_parser in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue Feb 14 01:59:21 2017 David Zeng
** Last update Tue Feb 14 01:59:21 2017 David Zeng
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "ar_header.h"

bool	is_archive(int fd)
{
  char	buf[SARMAG];

  if (read(fd, buf, SARMAG) <= 0)
    return (false);
  if (strncmp(buf, ARMAG, SARMAG) == 0)
    return (true);
  lseek(fd, 0, SEEK_SET);
  return (false);
}

static void	copy_str(char *filename, char *str)
{
  int		i;

  i = -1;
  while (++i < 16 && str[i] != '/')
    {
      filename[i] = str[i];
    }
  filename[i] = '\0';
}

void	skip_first(int fd)
{
  t_ar	ar;

  read(fd, &ar, sizeof(ar));
  lseek(fd, atol(ar.ar_size), SEEK_CUR);
}

int	get_next_ar_file(int fd, char *filename, size_t *offset)
{
  t_ar	ar;
  int	ret;

  ret = read(fd, &ar, sizeof(ar));
  copy_str(filename, ar.ar_name);
  *offset = lseek(fd, 0, SEEK_CUR);
  if (ret == 0 || *offset == (size_t)-1)
    return (-1);
  return (0);
}
