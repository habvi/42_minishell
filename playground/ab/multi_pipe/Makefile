NAME	:=	a.out

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
INCLUDES	:=	-I. -I../../../libft/includes/

LIBFT	:=	../../../libft/libft.a

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

PHONY += multi
multi:
	$(CC) $(CFLAGS) $(INCLUDES) multistage_pipe.c $(LIBFT)
#	@echo '<usage: ./a.out "cmd" "arg1" "arg2" "|" "cmd" "arg" "|" "cmd" "arg1" "arg2" "arg3" ...>'

.PHONY: $(PHONY)
