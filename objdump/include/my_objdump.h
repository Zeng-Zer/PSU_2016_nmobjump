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
# include "flags.h"
# include "ar_header.h"

# define MASK(val, mask) ((val & mask) == mask)

typedef struct	s_elf
{
  Elf64_Ehdr	ehdr;
  Elf64_Shdr	*shdr;
  char const	*filename;
  bool		is_archive;
}		t_elf;

typedef struct	s_pair
{
  Elf64_Word	first;
  char		*second;
}		t_pair;

extern char	*g_prog_name;

int		my_objdump(char const *filename);
int		parse_elf(t_elf *elf, int fd);
int		file_truncated(char const *filename);
void		write_header(t_elf *elf);

#endif /* !MY_OBJDUMP_H_ */
