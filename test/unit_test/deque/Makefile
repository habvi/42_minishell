SRCS		:=	test.c

OBJS_DIR	:=	objs
OBJS		:=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

LIBFT_DIR	:= ../../../libft
LIBFT		:= $(LIBFT_DIR)/libft.a

INCLUDES_DIR	:=	includes
INCLUDES	:=	-I$(LIBFT_DIR)/$(INCLUDES_DIR)/
DEPS		:=	$(OBJS:.o=.d)

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
MKDIR		:=	mkdir -p

NAME		:=	a.out
all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIBFT)

clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJS_DIR)
#	$(RM) -r $(OBJS_DIR) libft/

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
