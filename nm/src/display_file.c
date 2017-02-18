/*
** display_file.c for display_file in /home/zeng_d/rendu/PSU/PSU_2016_nmobjdump/nm
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Sat Feb 18 20:07:57 2017 David Zeng
** Last update Sat Feb 18 20:07:57 2017 David Zeng
*/

#include "my_nm.h"

static int	do_64(t_elf *elf, int fd, bool many)
{
  int		ret;

  if ((ret = parse_elf(elf, fd)) != 0)
    return (ret);
  if (write_all_symbol(elf, many) == 1)
    return (1);
  return (0);
}

static int	do_32(t_elf *elf, int fd, bool many)
{
  int		ret;

  if ((ret = parse_elf32(elf, fd)) != 0)
    return (ret);
  if (write_all_symbol32(elf, many) == 1)
    return (1);
  return (0);
}

int	display_file(char const *filename, int fd, size_t offset, bool many)
{
  t_elf	elf;
  int	ret;

  elf = (t_elf) {.shdr = NULL, .symtab = NULL, .s32r = NULL, .s32tab = NULL,
		 .symsize = 0, .filename = filename, .shstrtab = NULL,
		 .strtab = NULL, .file_start = offset};
  if (check_ident(&elf, fd) == 1)
    return (1);
  if (elf.is32 && (ret = do_32(&elf, fd, many)) != 0)
    return (ret);
  if (!elf.is32 && (ret = do_64(&elf, fd, many)) != 0)
    return (ret);
  free(elf.shdr);
  free(elf.symtab);
  free(elf.s32r);
  free(elf.s32tab);
  free(elf.shstrtab);
  free(elf.strtab);
  return (0);
}
