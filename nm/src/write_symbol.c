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

static char	get_type(t_elf *elf, Elf64_Sym *sym)
{
  bool		local;

  local = true;
  if (sym->st_shndx == SHN_ABS)
    return ('A');
  /* return ('?'); */
  if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
    local = false;
  /* printf("char: %c, info: %d\n", sym->st_info + 48, sym->st_info); */
  return (sym->st_info);
}

char            print_type(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char  c;

  if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
    c = 'u';
  else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    {
      c = 'W';
      if (sym->st_shndx == SHN_UNDEF)
        c = 'w';
    }
  else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK && ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
    {
      c = 'V';
      if (sym->st_shndx == SHN_UNDEF)
        c = 'v';
    }
  else if (sym->st_shndx == SHN_UNDEF)
    c = 'U';
  else if (sym->st_shndx == SHN_ABS)
    c = 'A';
  else if (sym->st_shndx == SHN_COMMON)
    c = 'C';
  else if (shdr[sym->st_shndx].sh_type == SHT_NOBITS
       && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'B';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym->st_shndx].sh_flags == SHF_ALLOC)
    c = 'R';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'D';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    c = 'T';
  else if (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC)
    c = 'D';
  else
    c = '?';
  if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
    c += 32;
  return c;
}

static int	comp_str(void const *str1, void const *str2)
{
  char const	**s1;
  char const	**s2;

  s1 = (char const**)str1;
  s2 = (char const**)str2;
  return (strcoll(*s1 + 19, *s2 + 19));
}

static char	*get_symbol_str(t_elf *elf, Elf64_Sym *sym)
{
  char		*name;
  char		type;
  char		*str;

  name = get_sym_name(elf, sym->st_name);
  /* type = get_type(elf, sym); */
  type = print_type(sym, elf->shdr);
  str = malloc(sizeof(char) * (strlen(name) + 20));
  if (type == 'U' || type == 'w')
    sprintf(str, "%16c %c %s", ' ', type, name);
  else
    sprintf(str, "%016lx %c %s", sym->st_value, type, name);
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
    printf("%s: %s: no symbols\n", g_prog_name, elf->filename);
}

int		write_all_symbol(t_elf *elf, bool many)
{
  size_t	i;
  size_t	j;
  Elf64_Sym	*sym;
  char		*tab[elf->symsize + 1];

  if (many)
    printf("\n%s:\n", elf->filename);
  j = 0;
  i = -1;
  while (++i < elf->symsize)
    {
      sym = &elf->symtab[i];
      if (sym->st_name != STN_UNDEF && sym->st_info != STT_FILE)
	tab[j++] = get_symbol_str(elf, sym);
    }
  tab[j] = NULL;
  setlocale(LC_ALL, "");
  qsort(tab, j, sizeof(char*), &comp_str);
  write_symbol(elf, tab);
  return (0);
}
