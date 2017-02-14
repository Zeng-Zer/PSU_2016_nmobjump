/*
** ar_header.h for ar_header in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue Feb 14 01:41:35 2017 David Zeng
** Last update Tue Feb 14 01:41:35 2017 David Zeng
*/

#ifndef AR_HEADER_H_
# define AR_HEADER_H_

# include <stdbool.h>
# include <stdlib.h>

# define ARMAG	"!<arch>\n"	/* String that begins an archive file.  */
# define SARMAG	8		/* Size of that string.  */
# define ARFMAG	"`\n"		/* String in ar_fmag at end of each header.  */

typedef struct	s_ar
{
  char		ar_name[16];		/* Member file name, sometimes / terminated. */
  char		ar_date[12];		/* File date, decimal seconds since Epoch.  */
  char		ar_uid[6];
  char		ar_gid[6];		/* User and group IDs, in ASCII decimal.  */
  char		ar_mode[8];		/* File mode, in ASCII octal.  */
  char		ar_size[10];		/* File size, in ASCII decimal.  */
  char		ar_fmag[2];		/* Always contains ARFMAG.  */
}		t_ar;

bool	is_archive(int fd);
int	get_next_ar_file(int fd, char *filename, size_t *offset);

#endif /* !AR_HEADER_H_ */
