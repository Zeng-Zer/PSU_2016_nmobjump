/*
** display_file.c for display_file in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Sat Feb 18 17:48:09 2017 David Zeng
** Last update Sat Feb 18 17:48:09 2017 David Zeng
*/

#include "my_objdump.h"

static int	do_64(t_elf *elf, int fd)
{
  int		ret;

  if ((ret = parse_elf(elf, fd)) != 0)
    return (ret);
  write_header(elf);
  write_all_sections(elf, fd);
  return (0);
}

static int	do_32(t_elf *elf, int fd)
{
  int		ret;

  if ((ret = parse_elf32(elf, fd)) != 0)
    return (ret);
  write_header32(elf);
  write_all_sections32(elf, fd);
  return (0);
}

int	display_file(char const *filename, int fd, size_t offset)
{
  t_elf	elf;
  int	ret;

  elf = (t_elf) {.shstrtab = NULL, .shdr = NULL, .s32r = NULL,
		 .file_start = offset, .filename = filename};
  if (check_ident(&elf, fd) == 1)
    return (1);
  if (elf.is32 && (ret = do_32(&elf, fd)) != 0)
    return (ret);
  if (!elf.is32 && (ret = do_64(&elf, fd)) != 0)
    return (ret);
  free(elf.shdr);
  free(elf.s32r);
  free(elf.shstrtab);
  if (offset == 0)
    close(fd);
  return (0);
}
