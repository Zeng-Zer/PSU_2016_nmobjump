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

int	display_file(char const *filename, int fd, size_t offset)
{
  t_elf	elf;
  int	ret;

  elf.shstrtab = NULL;
  elf.file_start = offset;
  elf.filename = filename;
  if ((ret = parse_elf(&elf, fd)) != 0)
    return (ret);
  write_header(&elf);
  write_all_sections(&elf, fd);
  free(elf.shdr);
  free(elf.shstrtab);
  return (0);
}
