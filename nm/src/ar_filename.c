/*
** ar_filename.c for ar_filename in /home/zeng_d/rendu/PSU/PSU_2016_nmobjdump/nm
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Fri Feb 17 20:56:54 2017 David Zeng
** Last update Fri Feb 17 20:56:54 2017 David Zeng
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "ar_header.h"

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

static int	count_newline(char *str)
{
  int		i;
  int		nl;

  i = -1;
  nl = 0;
  while (str[++i] != '\0')
    {
      if (str[i] == '\n')
	++nl;
    }
  return (nl);
}

static void	read_tab(char **tab, char *buf)
{
  int		i;
  int		j;
  int		start;

  i = 0;
  j = 0;
  while (buf[i] != '\0')
    {
      if (buf[i] != '\n' && buf[i] != '/')
	{
	  start = i;
	  while (buf[i] != '\n' && buf[i] != '/' && buf[i] != '\0')
	    ++i;
	  tab[j++] = &buf[start];
	}
      if (buf[i] != '\0')
	{
	  if (buf[i] == '/')
	    buf[i] = '\0';
	  ++i;
	}
    }
  tab[j] = NULL;
}

static char	*set_filenames(int fd, t_ar *ar, t_cont *cont, long int size)
{
  char		*buf;

  if ((buf = malloc(sizeof(char) * (size + 2))) == NULL ||
      read(fd, buf, size) != size)
    return (NULL);
  buf[size] = '\0';
  if ((cont->tab = malloc(sizeof(char*) * (count_newline(buf) + 2))) == NULL)
    return (NULL);
  read_tab(cont->tab, buf);
  if (read(fd, ar, sizeof(t_ar)) != sizeof(t_ar))
    return (NULL);
  return (ar_filename(ar, fd, cont));
}

char		*ar_filename(t_ar *ar, int fd, t_cont *cont)
{
  char		*name;
  char		buf[17];

  if (strncmp(ar->ar_name, "//", 2) == 0)
    {
      copy_str(buf, ar->ar_size, 16);
      return (set_filenames(fd, ar, cont, atol(buf)));
    }
  else if (strncmp(ar->ar_name, "/", 1) == 0)
    {
      if (!cont->tab)
	return (NULL);
      return (strdup(cont->tab[cont->idx++]));
    }
  name = malloc(sizeof(char) * 17);
  copy_str(name, ar->ar_name, 16);
  return (name);
}
