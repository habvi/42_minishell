SRCS		:=	$(wildcard *.c) # to do

# SRC_DIR		:=	src
OBJ_DIR		:=	obj
OBJS		:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

INCLUDE_DIR	:=	include
INCLUDES	:=	-I./$(INCLUDE_DIR)/
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
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)

# ------------------------
test: all
	@./a.out

valgrind: all
	@valgrind ./a.out

.PHONY:	test valgrind
