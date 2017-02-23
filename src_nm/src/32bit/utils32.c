/*
** utils.c for utils in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon Feb 13 13:06:06 2017 David Zeng
** Last update Mon Feb 13 13:06:06 2017 David Zeng
*/

#include "my_nm.h"

char		*read_section32(t_elf *elf, Elf32_Shdr *sh, int fd)
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
      free(section);
      return (NULL);
    }
  lseek(fd, old_pos, SEEK_SET);
  return (section);
}

char		*get_sh_name32(t_elf *elf, Elf32_Word sh_name)
{
  return (&elf->shstrtab[sh_name]);
}

char		*get_sym_name32(t_elf *elf, Elf32_Word sh_name)
{
  return (&elf->strtab[sh_name]);
}
