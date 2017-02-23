/*
** my_nm.h for my_nm in /home/zeng_d/test/trash/tarliba
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Wed Feb 15 21:28:30 2017 David Zeng
** Last update Wed Feb 15 21:28:30 2017 David Zeng
*/

#ifndef MY_NM_H_
# define MY_NM_H_

# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <elf.h>
# include <locale.h>
# include "ar_header.h"

# define MASK(val, mask) ((val & mask) == mask)

typedef struct	s_elf
{
  Elf64_Ehdr	ehdr;
  Elf64_Shdr	*shdr;
  Elf64_Sym	*symtab;
  Elf32_Ehdr	e32r;
  Elf32_Shdr	*s32r;
  Elf32_Sym	*s32tab;
  size_t	symsize;
  char const	*filename;
  char		*shstrtab;
  char		*strtab;
  size_t	file_start;
  bool		is32;
}		t_elf;

extern char	*g_prog_name;

int		my_nm(char const *filename, bool many);
int		parse_elf(t_elf *elf, int fd);
int		file_truncated(char const *filename);
char		*read_section(t_elf *elf, Elf64_Shdr *sh, int fd);
char		*get_sh_name(t_elf *elf, Elf64_Word sh_name);
char		*get_sym_name(t_elf *elf, Elf64_Word sh_name);
int		write_all_symbol(t_elf *elf, bool many);
int		display_file(char const *filename, int fd, size_t offset, bool);
int		check_ident(t_elf *elf, int fd);

// 32 BIT
char		*get_sym_name32(t_elf *elf, Elf32_Word sh_name);
char		*read_section32(t_elf *elf, Elf32_Shdr *sh, int fd);
char		*get_sh_name32(t_elf *elf, Elf32_Word sh_name);
int		parse_elf32(t_elf *elf, int fd);
int		write_all_symbol32(t_elf *elf, bool many);

#endif /* !MY_NM_H_ */
