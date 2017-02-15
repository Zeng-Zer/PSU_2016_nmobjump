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

int	skip_first(int fd)
{
  t_ar	ar;
  char	buf[17];
  int	i;

  if (read(fd, &ar, sizeof(ar)) <= 0)
    return (1);
  i = -1;
  while (ar.ar_size[++i] != '\0' && i < 16)
    buf[i] = ar.ar_size[i];
  buf[i] = '\0';
  if (atol(buf) == 0)
    return (1);
  if (lseek(fd, atol(buf), SEEK_CUR) == -1)
    return (1);
  return (0);
}

static void	copy_str(char *filename, char *str, int size_max)
{
  int		i;

  i = -1;
  while (++i < size_max && str[i] != '/')
    {
      filename[i] = str[i];
    }
  filename[i] = '\0';
}

static char	*get_filename(t_ar *ar, int fd)
{
  char		*name;

  name = NULL;
  if (strncmp(ar->ar_name, "//", 2) == 0 &&
      only_whitespace(ar->ar_date, 12) &&
      only_whitespace(ar->ar_uid, 6) && only_whitespace(ar->ar_gid, 6) &&
      only_whitespace(ar->ar_mode, 8))
    {
      name = malloc(sizeof(char) * atol(ar->ar_size));
      if (!name)
	exit(1);
      if (read(fd, name, atol(ar->ar_size)) <= 0 || atol(ar->ar_size) - 1 < 0)
	return (NULL);
      copy_str(name, name, atol(ar->ar_size));
      if (read(fd, ar, sizeof(t_ar)) <= 0)
	return (NULL);
      return (name);
    }
  name = malloc(sizeof(char) * 17);
  copy_str(name, ar->ar_name, 16);
  return (name);
}

int		get_next_ar_file(int fd, char **filename, size_t *offset)
{
  static size_t	next = 0;
  t_ar		ar;
  int		ret;
  char		buf[17];

  memset(&ar, 0, sizeof(t_ar));
  if (next != 0)
    lseek(fd, next, SEEK_SET);
  ret = read(fd, &ar, sizeof(t_ar));
  if (ret == 0)
    return (-1);
  *filename = get_filename(&ar, fd);
  if (*filename == NULL)
    return (1);
  *offset = lseek(fd, 0, SEEK_CUR);
  if (*offset == (size_t)-1)
    return (-1);
  if (ret == -1)
    return (1);
  strncpy(buf, ar.ar_size, 16);
  if (atol(buf) == 0)
    return (1);
  next = *offset + atol(buf);
  return (0);
}
