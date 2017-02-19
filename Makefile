##
## Makefile<PSU_2016_nmobjdump> for Makefile in /home/zeng_d
##
## Made by David Zeng
## Login   <zeng_d@epitech.net>
##
## Started on  Sat Feb 18 16:46:01 2017 David Zeng
## Last update Sat Feb 18 16:46:01 2017 David Zeng
##

NAME_NM		:= my_nm
NAME_OBJDUMP	:= my_objdump

DIR_NM		:= nm/
DIR_OBJDUMP	:= objdump/

MV		:= mv
RM		:= rm -f

all: $(NAME_NM) $(NAME_OBJDUMP)

$(NAME_NM):
	$(MAKE) -C $(DIR_NM)
	$(MV) $(DIR_NM)$(NAME_NM) ./

$(NAME_OBJDUMP):
	$(MAKE) -C $(DIR_OBJDUMP)
	$(MV) $(DIR_OBJDUMP)$(NAME_OBJDUMP) ./

clean:
	$(MAKE) -C $(DIR_NM) clean
	$(MAKE) -C $(DIR_OBJDUMP) clean

fclean:
	$(MAKE) -C $(DIR_NM) fclean
	$(MAKE) -C $(DIR_OBJDUMP) fclean
	$(RM) $(NAME_NM)
	$(RM) $(NAME_OBJDUMP)

re: fclean all

.PHONY: all clean fclean re
