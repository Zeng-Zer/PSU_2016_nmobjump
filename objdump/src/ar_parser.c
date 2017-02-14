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
#include "ar_header.h"

bool	is_archive(int fd)
{
  char	buf[SARMAG];

  if (read(fd, buf, SARMAG) == 0)
    return (false);
  if (strncmp(buf, ARMAG, SARMAG) == 0)
    return (true);
  lseek(fd, 0, SEEK_SET);
  return (false);
}

int	get_next_ar_file(int fd, char *filename)
{
  // TODO READ ARCHIVE AND GET NEXT FILE
  (void)fd;
  (void)filename;
  return (0);
}
