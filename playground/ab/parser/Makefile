NAME	:=	a.out

SRCS	:=	$(wildcard *.c)

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror
INCLUDES	:=	-I. -I../../../libft/includes/

LIBFT	:=	../../../libft/libft.a

PHONY += t
t:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(LIBFT)

.PHONY: $(PHONY)
