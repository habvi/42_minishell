NAME		=	a.out

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined

SRCS		=	test_hash.c
OBJS		=	test_hash.o

LIBFT_DIR	=	../../../libft
LIBFT		=	$(LIBFT_DIR)/libft.a
INCLUDES	=	-I$(LIBFT_DIR)/includes

all		: $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT)

$(OBJS)	: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean	:
	$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean	: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

FORCE	:

re		: fclean all

run		: all
	./$(NAME)

.PHONY	: all clean fclean re run FORCE