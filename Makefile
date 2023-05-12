NAME	:=	minishell

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
RL_FLAGS	:=	-lreadline
MKDIR		:=	mkdir -p

SRCS_DIR	:=	srcs
SRCS		:=	main.c

EXEC_DIR	:=	exec
SRCS		+=	$(EXEC_DIR)/exec.c

INPUT_DIR	:=	input
SRCS		+=	$(INPUT_DIR)/input.c

OBJ_DIR	:=	obj
OBJS	:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR	:=	libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

ifdef SANI
	CFLAGS += -g -fsanitize=address
endif

INCLUDE_DIR	:=	includes
INCLUDES	:=	-I./$(INCLUDE_DIR)/ -I$(LIBFT_DIR)/$(INCLUDE_DIR)/
DEPS		:=	$(OBJS:.o=.d)

PHONY	:= all
all		: $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(RL_FLAGS)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

PHONY += clean
clean	:
	$(RM) -r $(OBJ_DIR)

PHONY += fclean
fclean	: clean
	$(RM) $(NAME)

PHONY += re
re		: fclean all

PHONY += FORCE
FORCE	:

#--------------------------------------------
PHONY += run
run		: re
	./$(NAME)

PHONY += sani
sani	:
	make re SANI=1

PHONY += norm
norm	:
	python3 .github/sh/norm.py


#--------------------------------------------
# test.bats
PHONY += t
t		: re
	./.github/sh/test.bats


.PHONY: $(PHONY)
-include $(DEPS)
