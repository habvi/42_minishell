NAME		=	a.out

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined

VPATH 		= 	../../../srcs/path ../../../srcs/utils

SRCS		=	test_get_next_path.c \
				../../../srcs/path/get_next_path.c \
				../../../srcs/utils/x_ft_strdup.c \
				../../../srcs/utils/x_ft_strjoin.c \
				../../../srcs/utils/ft_abort.c

OBJS		=	test_get_next_path.o \
				get_next_path.o \
				x_ft_strdup.o \
				x_ft_strjoin.o \
				ft_abort.o

LIBFT_DIR	=	../../../libft
LIBFT		=	$(LIBFT_DIR)/libft.a

INCLUDES	=	-I ../../../includes -I$(LIBFT_DIR)/includes

all		: $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT)

%.o: %.c
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
