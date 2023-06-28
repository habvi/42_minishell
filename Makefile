
NAME		:=	minishell

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
RL_FLAGS	:=	-lreadline
MKDIR		:=	mkdir -p

SRCS_DIR	:=	srcs
SRCS		:=	destroy.c \
				init.c \
				main.c \
				repl.c

BUILTIN_DIR	:=	builtin
SRCS		+=	$(BUILTIN_DIR)/ft_cd.c \
				$(BUILTIN_DIR)/ft_cd_set_path.c \
				$(BUILTIN_DIR)/ft_echo.c \
				$(BUILTIN_DIR)/ft_env.c \
				$(BUILTIN_DIR)/ft_exit.c \
				$(BUILTIN_DIR)/ft_export.c \
				$(BUILTIN_DIR)/ft_pwd.c \
				$(BUILTIN_DIR)/ft_unset.c \
				$(BUILTIN_DIR)/is_option.c \
				$(BUILTIN_DIR)/str_to_legal_number.c

ENVIRONMENT	:=	environment
SRCS		+=	$(ENVIRONMENT)/clear.c \
				$(ENVIRONMENT)/declare_arg.c \
				$(ENVIRONMENT)/dup_env_key.c \
				$(ENVIRONMENT)/dup_env_value.c \
				$(ENVIRONMENT)/get_value.c \
				$(ENVIRONMENT)/init_environ.c \
				$(ENVIRONMENT)/init_old_pwd.c \
				$(ENVIRONMENT)/init_pwd.c \
				$(ENVIRONMENT)/is_key_exist.c \
				$(ENVIRONMENT)/print_detail.c \
				$(ENVIRONMENT)/print.c \
				$(ENVIRONMENT)/set.c \
				$(ENVIRONMENT)/unset.c

DEBUG_DIR	:=	debug
SRCS		+=	$(DEBUG_DIR)/put.c

EXEC_DIR	:=	exec
SRCS		+=	$(EXEC_DIR)/call_builtin_command.c \
				$(EXEC_DIR)/check_command.c \
				$(EXEC_DIR)/child_pipes.c \
				$(EXEC_DIR)/child_process.c \
				$(EXEC_DIR)/exec.c \
				$(EXEC_DIR)/get_exec_command.c \
				$(EXEC_DIR)/init.c \
				$(EXEC_DIR)/is_single_builtin.c \
				$(EXEC_DIR)/parent_pipes.c \
				$(EXEC_DIR)/parent_process.c \

INPUT_DIR	:=	input
SRCS		+=	$(INPUT_DIR)/input.c

TOKEN_DIR	:=	tokenize
SRCS		+=	$(TOKEN_DIR)/tokenize.c

UTILS_DIR	:=	utils
SRCS		+=	$(UTILS_DIR)/count_array.c \
				$(UTILS_DIR)/ft_abort.c \
				$(UTILS_DIR)/get_working_directory.c \
				$(UTILS_DIR)/is_valid_key.c \
				$(UTILS_DIR)/test_opendir.c

OBJS_DIR	:=	objs
OBJS		:=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

LIBFT_DIR	:=	libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

ifdef SANI
	CFLAGS += -g -fsanitize=address
endif

INCLUDES_DIR	:=	includes
INCLUDES		:=	-I./$(INCLUDES_DIR)/ -I$(LIBFT_DIR)/$(INCLUDES_DIR)/
DEPS			:=	$(OBJS:.o=.d)

.PHONY	: all
all		: $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(RL_FLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

.PHONY	: clean
clean	:
	$(RM) -r $(OBJS_DIR) $(LIBFT_DIR)/$(OBJS_DIR)

.PHONY	: fclean
fclean	: clean
	$(RM) $(NAME) $(LIBFT)

.PHONY	: re
re		: fclean all

.PHONY	: FORCE
FORCE	:

#--------------------------------------------
.PHONY	: run
run		: re
	./$(NAME)

.PHONY	: sani
sani	:
	make re SANI=1

.PHONY	: norm
norm	:
	python3 ./test/integration_test/norm.py


#--------------------------------------------
# test.bats
#.PHONY	: t
#t		: re
#	./.github/sh/test.bats

t		: all
	./test/unit_test/unit_test.sh

# test all
.PHONY		: test_all
test_all	: all
	python3 ./test/integration_test/run_all.py

# test multi pipe
.PHONY		: test_pipe
test_pipe	: all
	python3 ./test/integration_test/run_pipe.py

# test builtin echo
.PHONY		: test_echo
test_echo	: all
	python3 ./test/integration_test/run_echo.py

# test builtin exit
.PHONY		: test_exit
test_exit	: all
	python3 ./test/integration_test/run_exit.py

# test builtin export
.PHONY		: test_export
test_export	: all
	python3 ./test/integration_test/run_export.py

# test builtin pwd
.PHONY		: test_pwd
test_pwd	: all
	python3 ./test/integration_test/run_pwd.py

-include $(DEPS)
