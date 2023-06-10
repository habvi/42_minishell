NAME		=	a.out

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined

SRCS		=	test_legal_number.c \
				../../../srcs/builtin/str_to_legal_number.c

OBJS		=	test_legal_number.o \
				str_to_legal_number.o

INCLUDE		=	-I../../../includes -I../../../libft/includes

LIBFT_DIR	= ../../../libft
LIBFT		= $(LIBFT_DIR)/libft.a

all		: $(NAME)

$(NAME)	: $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBFT)

$(OBJS)	: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^

clean	:
	$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean	: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re		: fclean all

run		: all
	./$(NAME)

.PHONY	: all clean fclean re run