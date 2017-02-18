/*
** write_header.c for write_header in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue Feb 14 00:22:53 2017 David Zeng
** Last update Tue Feb 14 00:22:53 2017 David Zeng
*/

#include "my_objdump.h"

static t_pair const flag_map[9] =
{
  {HAS_RELOC, "HAS_RELOC"},
  {EXEC_P, "EXEC_P"},
  {HAS_LINENO, "HAS_LINENO"},
  {HAS_DEBUG, "HAS_DEBUG"},
  {HAS_SYMS, "HAS_SYMS"},
  {HAS_LOCALS, "HAS_LOCALS"},
  {DYNAMIC, "DYNAMIC"},
  {WP_TEXT, "WP_TEXT"},
  {D_PAGED, "D_PAGED"}
};

static t_pair const arch_map[10] =
{
  {0, "Unknown"},
  {2, "Sparc"},
  {3, "i386"},
  {8, "MIPS"},
  {0x14, "PowerPC"},
  {0x28, "ARM"},
  {0x2A, "SuperH"},
  {0x32, "IA-64"},
  {0x3E, "i386:x86-64"},
  {0xB7 , "AArch64"}
};

static void	print_flags(Elf32_Word flags)
{
  int		i;
  bool		has_flag;

  i = -1;
  has_flag = false;
  while (++i < 9)
    {
      if (MASK(flags, flag_map[i].first))
	{
	  if (has_flag)
	    printf(", ");
	  printf("%s", flag_map[i].second);
	  has_flag = true;
	}
    }
  if (has_flag)
    printf("\n");
  else
    printf("BFD_NO_FLAGS\n");
}

static inline const char	*get_arch(Elf32_Half arch)
{
  int				i;

  i = -1;
  while (++i < 10)
    {
      if (arch_map[i].first == arch)
	return (arch_map[i].second);
    }
  return ("Unknown");
}

void		write_header32(t_elf *elf)
{
  printf("\n%s:     file format %s\n", elf->filename, "elf32-i386");
  printf("architecture: %s, flags 0x%08x:\n", get_arch(elf->e32r.e_machine),
	 elf->e32r.e_flags);
  print_flags(elf->e32r.e_flags);
  printf("start address 0x%08x\n\n", elf->e32r.e_entry);
}
