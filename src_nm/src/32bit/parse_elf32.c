/*
** read_elf_header.c for read_elf_header in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon Feb 13 12:11:35 2017 David Zeng
** Last update Mon Feb 13 12:11:35 2017 David Zeng
*/

#include "my_nm.h"

static int	read_shdr(t_elf *elf, int fd)
{
  lseek(fd, elf->e32r.e_shoff - sizeof(Elf32_Ehdr), SEEK_CUR);
  if ((elf->s32r = malloc(sizeof(Elf32_Shdr) * elf->e32r.e_shnum)) == NULL)
    {
      fprintf(stderr, "Malloc out of memory\n");
      exit(1);
    }
  if (read(fd, elf->s32r, sizeof(Elf32_Shdr) * elf->e32r.e_shnum) !=
      (int)sizeof(Elf32_Shdr) * elf->e32r.e_shnum)
    return (file_truncated(elf->filename));
  return (0);
}

static int	read_sh(t_elf *elf, Elf32_Shdr *shdr, int fd)
{
  if (shdr->sh_type == SHT_STRTAB)
    {
      if (strncmp(get_sh_name(elf, shdr->sh_name), ".strtab", 7) == 0 &&
	  (elf->strtab = read_section32(elf, shdr, fd)) == NULL)
	return (1);
    }
  if (shdr->sh_type == SHT_SYMTAB)
    {
      elf->s32tab = (Elf32_Sym *)read_section32(elf, shdr, fd);
      if (!elf->s32tab)
	{
	  fprintf(stderr, "%s: %s: File format not recognized\n",
	  	  g_prog_name, elf->filename);
	  return (1);
	}
      elf->symsize = shdr->sh_size / sizeof(Elf32_Sym);
    }
  return (0);
}

static int	check_shdr(t_elf *elf, int fd)
{
  int		i;
  Elf32_Shdr	*shdr;

  i = -1;
  if ((elf->shstrtab = read_section32(elf, &elf->s32r[elf->e32r.e_shstrndx], fd))
      == NULL)
    {
      fprintf(stderr, "%s: %s: File format not recognized\n",
	      g_prog_name, elf->filename);
      return (1);
    }
  while (++i < elf->e32r.e_shnum)
    {
      shdr = &elf->s32r[i];
      if (shdr->sh_name > elf->s32r[elf->e32r.e_shstrndx].sh_size)
	{
	  fprintf(stderr, "%s: %s: File format not recognized\n",
	  	  g_prog_name, elf->filename);
	  return (1);
	}
      if (read_sh(elf, shdr, fd) == 1)
	return (1);
    }
  return (0);
}

int	parse_elf32(t_elf *elf, int fd)
{
  if (read_shdr(elf, fd) != 0)
    return (1);
  if (check_shdr(elf, fd) == 1)
    return (-1);
  return (0);
}
