NAME	:=	a.out

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror

ifdef SANI
	CFLAGS += -g -fsanitize=address
endif

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

PHONY += test
test	: re

PHONY += sani
sani	:
	make re SANI=1


.PHONY: $(PHONY)
