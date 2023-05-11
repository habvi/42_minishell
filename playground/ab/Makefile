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

PHONY += execve
execve:
	$(CC) $(CFLAGS) execve.c && ./$(NAME)

PHONY += dup
dup:
	$(CC) $(CFLAGS) dup.c && ./$(NAME) Makefile

PHONY += dup2
dup2:
	$(CC) $(CFLAGS) dup2.c && ./$(NAME)

.PHONY: $(PHONY)
