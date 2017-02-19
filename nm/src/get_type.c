/*
** get_type.c for get_type in /home/zeng_d/rendu/PSU/PSU_2016_nmobjdump/nm
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Fri Feb 17 20:43:55 2017 David Zeng
** Last update Fri Feb 17 20:43:55 2017 David Zeng
*/

#include "my_nm.h"

static char	type_uvw(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  (void)shdr;
  c = '?';
  if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
    c = 'u';
  else if (ELF64_ST_TYPE(sym->st_info) == STT_GNU_IFUNC)
    c = 'i';
  else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK &&
	   ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
    {
      c = 'V';
      if (sym->st_shndx == SHN_UNDEF)
	c = 'v';
    }
  else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    {
      c = 'W';
      if (sym->st_shndx == SHN_UNDEF)
	c = 'w';
    }
  return (c);
}

static char	type_shndx(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  (void)shdr;
  c = '?';
  if (sym->st_shndx == SHN_UNDEF)
    c = 'U';
  else if (sym->st_shndx == SHN_ABS)
    c = 'A';
  else if (sym->st_shndx == SHN_COMMON)
    c = 'C';
  return (c);
}

static char	type_brd(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = '?';
  if (shdr[sym->st_shndx].sh_type == SHT_NOBITS)
    c = 'B';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
	   (shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_MERGE) ||
	    shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_STRINGS |
					     SHF_MERGE)))
    c = 'R';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
	   shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'D';
  return (c);
}

static char	type_tdn(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = '?';
  if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
      shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    c = 'T';
  else if (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC ||
	   shdr[sym->st_shndx].sh_type == SHT_PREINIT_ARRAY ||
	   (shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
	    MASK(shdr[sym->st_shndx].sh_flags, SHF_TLS)))
    c = 'D';
  else if (shdr[sym->st_shndx].sh_type == SHT_GROUP)
    c = 'N';
  return (c);
}

static char	type_trn(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = '?';
  if ((shdr[sym->st_shndx].sh_type == SHT_FINI_ARRAY ||
       shdr[sym->st_shndx].sh_type == SHT_INIT_ARRAY) &&
      shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'T';
  else if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
	    MASK(shdr[sym->st_shndx].sh_flags, SHF_ALLOC)) ||
	   shdr[sym->st_shndx].sh_type == SHT_NOTE)
    c = 'R';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS)
    c = 'N';
  return (c);
}
