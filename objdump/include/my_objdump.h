/*
** my_objdump.h for my_objdump in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon Feb 13 12:01:44 2017 David Zeng
** Last update Mon Feb 13 12:01:44 2017 David Zeng
*/

#ifndef MY_OBJDUMP_H_
# define MY_OBJDUMP_H_

# include <elf.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "flags.h"
# include "ar_header.h"

# define MASK(val, mask) ((val & mask) == mask)

typedef struct	s_elf
{
  Elf64_Ehdr	ehdr;
  Elf64_Shdr	*shdr;
  char		*shstrtab;
  char const	*filename;
  size_t	file_start;
}		t_elf;

typedef struct	s_pair
{
  Elf64_Word	first;
  char		*second;
}		t_pair;

extern char	*g_prog_name;

int		my_objdump(char const *filename);
int		display_file(char const *filename, int fd, size_t offset);
int		parse_elf(t_elf *elf, int fd);
int		file_truncated(char const *filename);
void		write_header(t_elf *elf);
void		write_all_sections(t_elf *elf, int fd);
char		*read_section(t_elf *elf, Elf64_Shdr *sh, int fd);

#endif /* !MY_OBJDUMP_H_ */
