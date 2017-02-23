/*
** check_ident.c for check_ident in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Sat Feb 18 18:31:21 2017 David Zeng
** Last update Sat Feb 18 18:31:21 2017 David Zeng
*/

#include "my_objdump.h"

int	check_ident(t_elf *elf, int fd)
{
  int		ret;

  ret = read(fd, &elf->ehdr, sizeof(Elf64_Ehdr));
  if (ret == 0)
    return (1);
  if (ret != sizeof(Elf64_Ehdr) ||
      elf->ehdr.e_ident[EI_MAG0] != ELFMAG0 ||
      elf->ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
      elf->ehdr.e_ident[EI_MAG2] != ELFMAG2 ||
      elf->ehdr.e_ident[EI_MAG3] != ELFMAG3)
    {
      fprintf(stderr, "%s: %s: File format not recognized\n",
	      g_prog_name, elf->filename);
      return (1);
    }
  elf->is32 = elf->ehdr.e_ident[EI_CLASS] == ELFCLASS32;
  if (elf->is32)
    {
      memcpy(&elf->e32r, &elf->ehdr, sizeof(Elf32_Ehdr));
      lseek(fd, sizeof(Elf32_Ehdr) - sizeof(Elf64_Ehdr), SEEK_CUR);
    }
  return (0);
}
