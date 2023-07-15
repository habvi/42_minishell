NAME		=	a.out

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined

SRCS		=	test_exit.c \
				./../../../srcs/builtin/ft_exit.c \
				./../../../srcs/builtin/str_to_legal_number.c \
				./../../../srcs/utils/count_array.c \
				./../../../srcs/error/error_msg_1.c

OBJS		=	test_exit.o \
				ft_exit.o \
				str_to_legal_number.o \
				count_array.o \
				error_msg_1.o


LIBFT_DIR	=	./../../../libft
LIBFT		=	$(LIBFT_DIR)/libft.a

INCLUDES	=	-I./../../../includes -I./../../../libft/includes

all		: $(NAME)

$(NAME)	: $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(OBJS)	: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $^

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