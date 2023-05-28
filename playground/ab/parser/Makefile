NAME	:=	a.out

SRCS	:=	ast_node_new.c \
			ast_rule.c \
			calc.c \
			main.c \
			tokenize.c \
			util_token.c

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror
INCLUDES	:=	-I. -I../../../libft/includes/

LIBFT	:=	../../../libft/libft.a

PHONY += t
t:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(LIBFT)

.PHONY: $(PHONY)
