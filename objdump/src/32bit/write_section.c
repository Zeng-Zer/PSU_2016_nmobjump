/*
** write_section.c for write_section in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue Feb 14 12:10:59 2017 David Zeng
** Last update Tue Feb 14 12:10:59 2017 David Zeng
*/

#include <ctype.h>
#include "my_objdump.h"

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

static void	write_section(t_elf *elf, Elf64_Shdr *shdr, int fd)
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

void		write_all_sections(t_elf *elf, int fd)
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
