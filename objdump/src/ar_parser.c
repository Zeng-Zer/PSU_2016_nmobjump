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

int	skip_first(int fd)
{
  t_ar	ar;
  char	buf[17];

  if (read(fd, &ar, sizeof(ar)) <= 0)
    return (1);
  strncpy(buf, ar.ar_size, 16);
  if (atol(buf) == 0)
    return (1);
  if (lseek(fd, atol(buf), SEEK_CUR) == -1)
    return (1);
  return (0);
}

int		get_next_ar_file(int fd, char *filename, size_t *offset)
{
  static size_t	next = 0;
  t_ar		ar;
  int		ret;
  char		buf[17];

  if (next != 0)
    lseek(fd, next, SEEK_SET);
  ret = read(fd, &ar, sizeof(ar));
  copy_str(filename, ar.ar_name);
  *offset = lseek(fd, 0, SEEK_CUR);
  if (ret == 0 || *offset == (size_t)-1)
    return (-1);
  if (ret == -1)
    return (1);
  strncpy(buf, ar.ar_size, 16);
  if (atol(buf) == 0)
    return (1);
  next = *offset + atol(buf);
  return (0);
}
