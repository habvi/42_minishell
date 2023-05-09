NAME	:=	a.out

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror

PHONY := fork
fork:
	$(CC) $(CFLAGS) fork.c && ./$(NAME)

PHONY += wait
wait:
	$(CC) $(CFLAGS) wait.c && ./$(NAME)

PHONY += pipe
pipe:
	$(CC) $(CFLAGS) pipe.c && ./$(NAME)

.PHONY: $(PHONY)
