NAME	:=	a.out

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror

all		:= $(NAME)

$(NAME)	: main.o
	$(CC) $(CFLAGS) -o $@ main.o

main.o	: main.c
	$(CC) $(CFLAGS) -o $@ -c main.c

.PHONY: $(PHONY)
