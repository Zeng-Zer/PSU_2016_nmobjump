/*
** write_symbol.c for write_symbol in /home/zeng_d/test/trash/tarliba
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Thu Feb 16 00:12:52 2017 David Zeng
** Last update Thu Feb 16 00:12:52 2017 David Zeng
*/

#include "my_nm.h"

static int	get_symbol(t_elf *elf, Elf64_Sym *sym)
{
  Elf64_Shdr	*shdr;

  if (sym->st_shndx == SHN_UNDEF)
    {
      printf("test\n");
      shdr = &elf->shdr[elf->symlink];
      printf("%s\n", get_sym_name(elf, sym->st_name));
    }
  return (0);
}

int	write_symbol(t_elf *elf, Elf64_Sym *sym)
{
  get_symbol(elf, sym);
  printf("%016lx C %s\n", sym->st_value, get_sym_name(elf, sym->st_name));
  return (0);
}
