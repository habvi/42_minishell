NAME		=	a.out

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined

SRCS		=	test_sq_str.c

OBJS		=	$(SRCS:%.c=%.o)

LIBFT_DIR	= ../../libft
LIBFT		= $(LIBFT_DIR)/libft.a

all		: $(NAME)

$(NAME)	: $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(OBJS)	: $(SRCS)
	$(CC) $(CFLAGS) -c $^

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
