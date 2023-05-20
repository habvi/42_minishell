NAME		= a.out

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

ifdef SANI
	CFLAGS	+= -g -fsanitized=address
endif

LIBFT_DIR	= ../../libft
LIBFT		= $(LIBFT_DIR)/libft.a

all	:	$(NAME)

$(NAME)	: parse_arithmetic_operation.c
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $< -o $(NAME) $(LIBFT)

re	:
	@$(RM) $(NAME)
	@make all

run	: all
	./$(NAME)
