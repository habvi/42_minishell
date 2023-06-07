NAME	:=	a.out

SRCS	:=	ast_node_new.c \
			ast_rule.c \
			ast_utils.c \
			calc.c \
			main.c \
			token_utils.c \
			tokenize.c

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
INCLUDES	:=	-I. -I../../../libft/includes/

LIBFT	:=	../../../libft/libft.a

PHONY += t
t:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(LIBFT)

.PHONY: $(PHONY)
