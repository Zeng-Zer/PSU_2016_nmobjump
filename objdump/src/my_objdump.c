/*
** my_objdump.c for my_objdump in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon Feb 13 12:03:30 2017 David Zeng
** Last update Mon Feb 13 12:03:30 2017 David Zeng
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_objdump.h"

static int	open_file(char const *filename)
{
  int		fd;

  fd = open(filename, O_DIRECTORY);
  if (fd != -1)
    {
      close(fd);
      fprintf(stderr, "%s: Warning: '%s' is not an ordinary file\n",
	      g_prog_name, filename);
      return (-1);
    }
  fd = open(filename, O_RDONLY);
  if (fd == -1)
    fprintf(stderr, "%s: '%s': No such file\n", g_prog_name, filename);
  return (fd);
}

static int	display_file(char const *filename, int fd)
{
  t_elf		elf;

  elf.filename = filename;
  if (parse_elf(&elf, fd) != 0)
    return (1);
  write_header(&elf);
  free(elf.shdr);
  return (0);
}

int		my_objdump(char const *filename)
{
  int		fd;

  if ((fd = open_file(filename)) == -1)
    return (1);
  // TODO ARCHIVE
  return (display_file(filename, fd));
}
