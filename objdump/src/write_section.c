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

void	write_section(t_elf *elf, Elf64_Shdr *shdr, int fd)
{
  printf("Contents of section %s:\n", &elf->shstrtab[shdr->sh_name]);
}
