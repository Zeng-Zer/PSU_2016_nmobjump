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
	{
	  printf("Contents of section %s:\n", &elf->shstrtab[shdr->sh_name]);
	  write_section(elf, shdr, fd);
	}
    }
}

static int	display_file(char const *filename, int fd, size_t offset)
{
  t_elf		elf;
  int		ret;

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

static int	loop_archive(int fd)
{
  char		*filename;
  int		ret;
  int		ret2;
  int		ret3;
  size_t	offset;

  ret2 = 0;
  skip_first(fd);
  filename = NULL;
  while ((ret = get_next_ar_file(fd, &filename, &offset)) == 0)
    {
      if ((ret3 = display_file(filename, fd, offset)) == 1)
	ret2 = 1;
      free(filename);
      if (ret3 == -1)
	{
	  ret = 1;
	  break;
	}
    }
  if (ret == 1)
    return (-1);
  return (ret2);
}

int		my_objdump(char const *filename)
{
  int		fd;
  int		ret;

  if ((fd = open_file(filename)) == -1)
    return (1);
  if (is_archive(fd))
    {
      printf("In archive %s:\n", filename);
      if ((ret = loop_archive(fd)) == -1)
	{
	  fprintf(stderr, "%s: %s: Malformed archive\n", g_prog_name, filename);
	  return (1);
	}
      return (ret);
    }
  return (display_file(filename, fd, 0));
}
