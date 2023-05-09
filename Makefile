NAME	:=	a.out

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror

PHONY := fork
fork:
	$(CC) $(CFLAGS) fork.c && ./$(NAME)

.PHONY: $(PHONY)
