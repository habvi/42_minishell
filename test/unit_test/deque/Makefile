PREFIX		:=	../../libft/srcs/ft_deque
SRCS		:=	test.c \
				$(PREFIX)/dq_add_back.c \
				$(PREFIX)/dq_add_front.c \
				$(PREFIX)/dq_clear_all.c \
				$(PREFIX)/dq_clear_node.c \
				$(PREFIX)/dq_is_empty.c \
				$(PREFIX)/dq_new.c \
				$(PREFIX)/dq_node_new.c \
				$(PREFIX)/dq_pop_back.c \
				$(PREFIX)/dq_pop_front.c \
				$(PREFIX)/dq_print.c \
				$(PREFIX)/dq_set_node.c

# SRC_DIR		:=	src
OBJ_DIR		:=	../../libft/objs
OBJS		:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR	:= ../../libft
LIBFT		:= $(LIBFT_DIR)/libft.a

INCLUDE_DIR	:=	includes
INCLUDES	:=	-I$(LIBFT_DIR)/$(INCLUDE_DIR)/
DEPS		:=	$(OBJS:.o=.d)

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
MKDIR		:=	mkdir -p

NAME		:=	a.out
all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT)

clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJ_DIR)
#	$(RM) -r $(OBJ_DIR) libft/

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

# ------------------------
test: all
	@./a.out

val: all
	@valgrind ./a.out

.PHONY: all clean fclean re test val
