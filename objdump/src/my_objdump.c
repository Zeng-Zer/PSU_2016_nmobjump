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
#include <string.h>
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

static void	write_all_sections(t_elf *elf, int fd)
{
  int		i;
  Elf64_Shdr	*shdr;
  Elf64_Word	type;
  char		*name;

  i = -1;
  while (++i < elf->ehdr.e_shnum)
    {
      shdr = &elf->shdr[i];
      type = shdr->sh_type;
      name = &elf->shstrtab[shdr->sh_name];
      if (type != SHT_NULL && type != SHT_NOBITS && type != SHT_SYMTAB &&
      	  strcmp(name, ".shstrtab") != 0 && strcmp(name, ".strtab") != 0 &&
	  ((MASK(elf->ehdr.e_flags, HAS_RELOC) && type != SHT_RELA) ||
	   !MASK(elf->ehdr.e_flags, HAS_RELOC)) &&
	  shdr->sh_size != 0)
	write_section(elf, shdr, fd);
    }
}

static int	display_file(char const *filename, int fd)
{
  t_elf		elf;

  elf.shstrtab = NULL;
  elf.file_start = 0;
  elf.filename = filename;
  if (parse_elf(&elf, fd) != 0)
    return (1);
  write_header(&elf);
  write_all_sections(&elf, fd);
  free(elf.shdr);
  free(elf.shstrtab);
  return (0);
}

static int	loop_archive(int fd)
{
  char		filename[256];

  while (get_next_ar_file(fd, filename) == 0)
    {
      if (display_file(filename, fd) == 1)
	return (1);
    }
  return (0);
}

int		my_objdump(char const *filename)
{
  int		fd;

  if ((fd = open_file(filename)) == -1)
    return (1);
  if (is_archive(fd))
    {
      printf("In archive %s:\n", filename);
      return (loop_archive(fd));
    }
  return (display_file(filename, fd));
}
