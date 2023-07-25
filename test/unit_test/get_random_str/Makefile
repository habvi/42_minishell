NAME		=	a.out

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined

SRCS		=	test_get_random_str.c

SRCS		=	test_get_random_str.c \
				../../../srcs/utils/get_random_str.c \
				../../../srcs/utils/ft_abort.c \
				../../../srcs/error/error_msg_3.c

OBJS		=	test_get_random_str.o \
				get_random_str.o \
				ft_abort.o \
				error_msg_3.o

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
