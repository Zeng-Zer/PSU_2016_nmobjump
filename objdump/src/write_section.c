/*
** write_section.c for write_section in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue Feb 14 12:10:59 2017 David Zeng
** Last update Tue Feb 14 12:10:59 2017 David Zeng
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "my_objdump.h"

char		*read_section(t_elf *elf, Elf64_Shdr *sh, int fd)
{
  char		*section;
  size_t	old_pos;

  section = malloc(sizeof(char) * (sh->sh_size));
  if (!section)
    {
      fprintf(stderr, "Malloc out of memory\n");
      exit(1);
    }
  old_pos = lseek(fd, 0, SEEK_CUR);
  lseek(fd, elf->file_start + sh->sh_offset, SEEK_SET);
  if (read(fd, section, sh->sh_size) != (int)sh->sh_size)
    {
      file_truncated(elf->filename);
      free(section);
      return (NULL);
    }
  lseek(fd, old_pos, SEEK_SET);
  return (section);
}

static void	print_address(unsigned char *section, size_t size)
{
  size_t	i;
  int		j;
  int		k;
  int		nb_printed;

  nb_printed = 0;
  j = -1;
  i = 0;
  while (++j < 4)
    {
      k = -1;
      while (++k < 4)
	{
	  if (i < size)
	    nb_printed += printf("%02x", section[i]);
	  ++i;
	}
      nb_printed += printf(" ");
    }
  while (nb_printed++ < 37)
    printf(" ");
}

static void	get_addr_nb(Elf64_Addr addr, size_t size, char *str)
{
  char		buf[256];
  size_t	len;

  sprintf(buf, "%lx", addr + size);
  len = strlen(buf);
  len = len > 4 ? len : 4;
  sprintf(buf, "%lu", len);
  strcpy(str, " %0");
  strcat(str, buf);
  strcat(str, "lx ");
}

static void	write_content(char *section, size_t size, Elf64_Addr addr)
{
  size_t	i;
  char		buf[16];

  i = -1;
  get_addr_nb(addr, size, buf);
  while (++i < size)
    {
      if (i != 0 && i % 16 == 0)
	printf("\n");
      if (i % 16 == 0)
	{
	  printf(buf, addr);
	  print_address((unsigned char *)section + i, size - i);
	  addr += 16;
	}
      if (isprint(section[i]))
	printf("%c", section[i]);
      else
	printf(".");
    }
  while (i++ % 16 != 0)
    printf(" ");
  printf("\n");
}

void		write_section(t_elf *elf, Elf64_Shdr *shdr, int fd)
{
  char		*section;
  Elf64_Addr	addr;

  section = read_section(elf, shdr, fd);
  if (section == NULL)
    return ((void)file_truncated(elf->filename));
  addr = shdr->sh_addr;
  write_content(section, shdr->sh_size, addr);
  free(section);
}
