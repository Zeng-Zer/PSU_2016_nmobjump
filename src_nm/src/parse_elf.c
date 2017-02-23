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
  lseek(fd, elf->ehdr.e_shoff - sizeof(Elf64_Ehdr), SEEK_CUR);
  if ((elf->shdr = malloc(sizeof(Elf64_Shdr) * elf->ehdr.e_shnum)) == NULL)
    {
      fprintf(stderr, "Malloc out of memory\n");
      exit(1);
    }
  if (read(fd, elf->shdr, sizeof(Elf64_Shdr) * elf->ehdr.e_shnum) !=
      (int)sizeof(Elf64_Shdr) * elf->ehdr.e_shnum)
    return (file_truncated(elf->filename));
  return (0);
}

static int	read_sh(t_elf *elf, Elf64_Shdr *shdr, int fd)
{
  if (shdr->sh_type == SHT_STRTAB)
    {
      if (strncmp(get_sh_name(elf, shdr->sh_name), ".strtab", 7) == 0 &&
	  (elf->strtab = read_section(elf, shdr, fd)) == NULL)
	return (1);
    }
  if (shdr->sh_type == SHT_SYMTAB)
    {
      elf->symtab = (Elf64_Sym *)read_section(elf, shdr, fd);
      if (!elf->symtab)
	{
	  fprintf(stderr, "%s: %s: File format not recognized\n",
		  g_prog_name, elf->filename);
	  return (1);
	}
      elf->symsize = shdr->sh_size / sizeof(Elf64_Sym);
    }
  return (0);
}

static int	check_shdr(t_elf *elf, int fd)
{
  int		i;
  Elf64_Shdr	*shdr;

  i = -1;
  if ((elf->shstrtab = read_section(elf, &elf->shdr[elf->ehdr.e_shstrndx], fd))
      == NULL)
    {
      fprintf(stderr, "%s: %s: File format not recognized\n",
	      g_prog_name, elf->filename);
      return (1);
    }
  while (++i < elf->ehdr.e_shnum)
    {
      shdr = &elf->shdr[i];
      if (shdr->sh_name > elf->shdr[elf->ehdr.e_shstrndx].sh_size)
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

int	parse_elf(t_elf *elf, int fd)
{
  if (read_shdr(elf, fd) != 0)
    return (1);
  if (check_shdr(elf, fd) == 1)
    return (-1);
  return (0);
}
