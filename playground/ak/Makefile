NAME		= a.out

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

ifdef SANI
	CFLAGS	+= -g -fsanitized=address
endif

all	:	$(NAME)

$(NAME)	: parse_arithmetic_operation.c
	$(CC) $(CFLAGS) $< -o $(NAME)

run	: all
	./$(NAME)
