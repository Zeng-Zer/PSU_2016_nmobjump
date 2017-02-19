/*
** write_symbol.c for write_symbol in /home/zeng_d/test/trash/tarliba
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Thu Feb 16 00:12:52 2017 David Zeng
** Last update Thu Feb 16 00:12:52 2017 David Zeng
*/

#include "my_nm.h"
#include "get_type32.c"

static char	(* const type_sym[5])(Elf32_Sym*, Elf32_Shdr*) =
{
  type_uvw32,
  type_shndx32,
  type_brd32,
  type_tdn32,
  type_trn32
};

static char	get_type(Elf32_Sym *sym, Elf32_Shdr *shdr)
{
  char		c;
  int		i;

  i = -1;
  while (++i < 5)
    {
      if ((c = type_sym[i](sym, shdr)) != '?')
	break;
    }
  if (c != '?' && c != 'i' && ELF32_ST_BIND(sym->st_info) == STB_LOCAL)
    c += 32;
  return c;
}

static int	comp_str(void const *str1, void const *str2)
{
  char const	**s1;
  char const	**s2;

  s1 = (char const**)str1;
  s2 = (char const**)str2;
  return (strcoll(*s1 + 11, *s2 + 11));
}

static char	*get_symbol_str(t_elf *elf, Elf32_Sym *sym)
{
  char		*name;
  char		type;
  char		*str;

  name = get_sym_name(elf, sym->st_name);
  type = get_type(sym, elf->s32r);
  str = malloc(sizeof(char) * (strlen(name) + 12));
  if (type == 'U' || type == 'w' || type == 'v')
    sprintf(str, "%8c %c %s", ' ', type, name);
  else
    sprintf(str, "%08x %c %s", sym->st_value, type, name);
  return (str);
}

static void	write_symbol(t_elf *elf, char **tab)
{
  int		i;

  i = -1;
  while (tab[++i] != NULL)
    {
      printf("%s\n", tab[i]);
      free(tab[i]);
    }
  if (i == 0)
    fprintf(stderr, "%s: %s: no symbols\n", g_prog_name, elf->filename);
}

int		write_all_symbol32(t_elf *elf, bool many)
{
  size_t	i;
  size_t	j;
  Elf32_Sym	*sym;
  char		*tab[elf->symsize + 1];

  if (many)
    printf("\n%s:\n", elf->filename);
  j = 0;
  i = -1;
  while (++i < elf->symsize)
    {
      sym = &elf->s32tab[i];
      if (sym->st_name != STN_UNDEF && sym->st_info != STT_FILE)
	tab[j++] = get_symbol_str(elf, sym);
    }
  tab[j] = NULL;
  setlocale(LC_ALL, "");
  qsort(tab, j, sizeof(char*), &comp_str);
  write_symbol(elf, tab);
  return (0);
}
