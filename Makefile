NAME	:=	a.out

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror

PHONY := fork
fork:
	$(CC) $(CFLAGS) fork.c && ./$(NAME)

PHONY := wait
wait:
	$(CC) $(CFLAGS) wait.c && ./$(NAME)

.PHONY: $(PHONY)
