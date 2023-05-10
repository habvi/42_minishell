NAME	:=	a.out

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror

ifdef SANI
	CFLAGS += -g -fsanitize=address
endif

#--------------------------------------------
# src
#--------------------------------------------
SRC_DIR		:= srcs


#--------------------------------------------
# include
#--------------------------------------------
INCLUDE_DIR	:=	includes


PHONY	:= all
all		: $(NAME)

$(NAME)	: main.o
	$(CC) $(CFLAGS) -o $@ main.o

main.o	: main.c
	$(CC) $(CFLAGS) -o $@ -c main.c

PHONY += clean
clean	:
	$(RM) main.o

PHONY += fclean
fclean	: clean
	$(RM) $(NAME)

PHONY += re
re		: fclean all


PHONY += sani
sani	:
	make re SANI=1

PHONY += norm
norm	:
	python3 .github/sh/norm.py


.PHONY: $(PHONY)
