
NAME		:=	minishell

UNAME 		:= $(shell uname)

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
ifeq ($(UNAME), Linux)
	CFLAGS	+=	-pedantic
endif

ifeq ($(UNAME), Linux)
	RL_FLAGS	:=	-lreadline
else
ifeq ($(UNAME), Darwin)
	RL_FLAGS	:= -L$(shell brew --prefix readline)/lib -lreadline
endif
endif

MKDIR		:=	mkdir -p

SRCS_DIR	:=	srcs
SRCS		:=	analyze_minishell_option.c \
				destroy.c \
				init.c \
				main.c \
				repl.c

BUILTIN_DIR	:=	builtin
FT_CD_DIR	:=	ft_cd
SRCS		+=	$(BUILTIN_DIR)/$(FT_CD_DIR)/canonicalize.c \
				$(BUILTIN_DIR)/$(FT_CD_DIR)/canonicalize_convert.c \
				$(BUILTIN_DIR)/$(FT_CD_DIR)/canonicalize_exception.c \
				$(BUILTIN_DIR)/$(FT_CD_DIR)/canonicalize_sep_join.c \
				$(BUILTIN_DIR)/$(FT_CD_DIR)/chdir.c \
				$(BUILTIN_DIR)/$(FT_CD_DIR)/ft_cd.c \
				$(BUILTIN_DIR)/$(FT_CD_DIR)/search_cdpath.c \
				$(BUILTIN_DIR)/$(FT_CD_DIR)/set_path.c \
				$(BUILTIN_DIR)/$(FT_CD_DIR)/update_pwd.c \
				$(BUILTIN_DIR)/ft_declare.c \
				$(BUILTIN_DIR)/ft_echo.c \
				$(BUILTIN_DIR)/ft_env.c \
				$(BUILTIN_DIR)/ft_exit.c \
				$(BUILTIN_DIR)/ft_export.c \
				$(BUILTIN_DIR)/ft_pwd.c \
				$(BUILTIN_DIR)/ft_unset.c \
				$(BUILTIN_DIR)/is_option.c \
				$(BUILTIN_DIR)/str_to_legal_number.c

VAR_DIR		:=	variables
SRCS		+=	$(VAR_DIR)/add.c \
				$(VAR_DIR)/clear.c \
				$(VAR_DIR)/convert.c \
				$(VAR_DIR)/declare_all.c \
				$(VAR_DIR)/declare_arg.c \
				$(VAR_DIR)/dup_var_key.c \
				$(VAR_DIR)/dup_var_value.c \
				$(VAR_DIR)/env_print.c \
				$(VAR_DIR)/get_var_info.c \
				$(VAR_DIR)/is_key_exist.c \
				$(VAR_DIR)/join.c \
				$(VAR_DIR)/print_detail.c \
				$(VAR_DIR)/set_default_environ.c \
				$(VAR_DIR)/set_default_old_pwd.c \
				$(VAR_DIR)/set_default_pwd.c \
				$(VAR_DIR)/unset.c \
				$(VAR_DIR)/var_create_var_info.c \
				$(VAR_DIR)/var_sort_elems.c

DEBUG_DIR	:=	debug
SRCS		+=	$(DEBUG_DIR)/debug_print_ast.c \
				$(DEBUG_DIR)/debug_print_ast_sub.c \
				$(DEBUG_DIR)/debug_print_dp_table.c \
				$(DEBUG_DIR)/debug_token_dq.c \
				$(DEBUG_DIR)/debug_token_dq_sub.c \
				$(DEBUG_DIR)/put.c

ERROR_DIR	:=	error
SRCS		+=	$(ERROR_DIR)/error_msg_1.c \
				$(ERROR_DIR)/error_msg_2.c \
				$(ERROR_DIR)/error_msg_set_status.c

EXEC_DIR	:=	exec
EXPAND_DIR	:=	expand
SRCS		+=	$(EXEC_DIR)/$(EXPAND_DIR)/concat_tokens.c  \
				$(EXEC_DIR)/$(EXPAND_DIR)/dirp.c\
				$(EXEC_DIR)/$(EXPAND_DIR)/expand_for_heredoc.c\
				$(EXEC_DIR)/$(EXPAND_DIR)/expand_for_redirect.c\
				$(EXEC_DIR)/$(EXPAND_DIR)/expand_parameter.c\
				$(EXEC_DIR)/$(EXPAND_DIR)/expand_var_in_heredoc.c\
				$(EXEC_DIR)/$(EXPAND_DIR)/expansion.c  \
				$(EXEC_DIR)/$(EXPAND_DIR)/is_pattern_match.c  \
				$(EXEC_DIR)/$(EXPAND_DIR)/pattern_matching.c  \
				$(EXEC_DIR)/$(EXPAND_DIR)/remove_empty_tokens.c  \
				$(EXEC_DIR)/$(EXPAND_DIR)/sort_filenames.c  \
				$(EXEC_DIR)/$(EXPAND_DIR)/split_expand_word.c  \
				$(EXEC_DIR)/$(EXPAND_DIR)/substr_before_dollar.c  \
				$(EXEC_DIR)/$(EXPAND_DIR)/wildcard.c  \
				$(EXEC_DIR)/$(EXPAND_DIR)/word_split.c  \
				$(EXEC_DIR)/backup_fd.c \
				$(EXEC_DIR)/call_builtin_command.c \
				$(EXEC_DIR)/child_pipes.c \
				$(EXEC_DIR)/child_process.c \
				$(EXEC_DIR)/close_proc_fds.c \
				$(EXEC_DIR)/exec.c \
				$(EXEC_DIR)/exec_command.c \
				$(EXEC_DIR)/exec_external_command.c \
				$(EXEC_DIR)/get_exec_command.c \
				$(EXEC_DIR)/handle_node.c \
				$(EXEC_DIR)/is_single_builtin.c \
				$(EXEC_DIR)/parent_pipes.c \
				$(EXEC_DIR)/parent_process.c \
				$(EXEC_DIR)/redirect_connect_to_proc.c \
				$(EXEC_DIR)/redirect_init_del.c \
				$(EXEC_DIR)/redirect_open_fd.c \
				$(EXEC_DIR)/redirects.c \
				$(EXEC_DIR)/single_builtin.c \

INPUT_DIR	:=	input
SRCS		+=	$(INPUT_DIR)/input.c

PARSE_DIR	:=	parse
HEREDOC_DIR	:=	heredoc
SRCS		+=	$(PARSE_DIR)/$(HEREDOC_DIR)/create_heredoc_filename.c \
				$(PARSE_DIR)/$(HEREDOC_DIR)/execute_heredoc_each.c \
				$(PARSE_DIR)/$(HEREDOC_DIR)/heredoc.c \
				$(PARSE_DIR)/$(HEREDOC_DIR)/open_heredoc_fd.c \
				$(PARSE_DIR)/$(HEREDOC_DIR)/read_input_save_to_fd.c \
				$(PARSE_DIR)/abstruct_syntax_tree.c \
				$(PARSE_DIR)/ast_convert_kind.c \
				$(PARSE_DIR)/ast_dup_token.c \
				$(PARSE_DIR)/ast_error.c \
				$(PARSE_DIR)/destroy_ast.c \
				$(PARSE_DIR)/get_node_kind_str.c \
				$(PARSE_DIR)/is_node_kind.c \
				$(PARSE_DIR)/is_parenthesis_concatted.c \
				$(PARSE_DIR)/is_valid_redirect_syntax.c \
				$(PARSE_DIR)/move_redirect_from_command.c \
				$(PARSE_DIR)/new_ast_node.c \
				$(PARSE_DIR)/parse.c \
				$(PARSE_DIR)/pre_parse_syntax.c \
				$(PARSE_DIR)/transfer_redirect_from_command.c

PATH_DIR	:=	path
SRCS		+=	$(PATH_DIR)/create_exec_path.c \
				$(PATH_DIR)/create_executable_or_accessible_path.c \
				$(PATH_DIR)/create_split_src_paths.c \
				$(PATH_DIR)/get_next_path.c

SIGNAL_DIR	:=	signal
SRCS		+=	$(SIGNAL_DIR)/signal.c

TOKEN_DIR	:=	tokenize
SRCS		+=	$(TOKEN_DIR)/del_token.c \
				$(TOKEN_DIR)/get_token_kind.c \
				$(TOKEN_DIR)/get_token_str.c \
				$(TOKEN_DIR)/get_token_tail.c \
				$(TOKEN_DIR)/is_closed_paren.c \
				$(TOKEN_DIR)/is_closed_quote.c \
				$(TOKEN_DIR)/is_concat_to_next.c \
				$(TOKEN_DIR)/is_token_kind.c \
				$(TOKEN_DIR)/is_token_kind_from_node.c \
				$(TOKEN_DIR)/is_token_kind_from_node_subshell.c \
				$(TOKEN_DIR)/is_token_str.c \
				$(TOKEN_DIR)/remove_quote.c \
				$(TOKEN_DIR)/set_is_quoted_arr.c \
				$(TOKEN_DIR)/set_token_kind.c \
				$(TOKEN_DIR)/set_token_quote_all.c \
				$(TOKEN_DIR)/tokenize.c \
				$(TOKEN_DIR)/tokenize_line.c

UTILS_DIR	:=	utils
SRCS		+=	$(UTILS_DIR)/count_array.c \
				$(UTILS_DIR)/extend_str.c \
				$(UTILS_DIR)/ft_abort.c \
				$(UTILS_DIR)/ft_gnl.c \
				$(UTILS_DIR)/get_random_str.c \
				$(UTILS_DIR)/get_working_directory.c \
				$(UTILS_DIR)/is_valid_key.c \
				$(UTILS_DIR)/is_valid_path.c \
				$(UTILS_DIR)/x_ft_itoa.c \
				$(UTILS_DIR)/x_ft_strdup.c \
				$(UTILS_DIR)/x_ft_strjoin.c \
				$(UTILS_DIR)/x_ft_substr.c

OBJS_DIR	:=	objs
OBJS		:=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

LIBFT_DIR	:=	libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

ifdef SANI
	CFLAGS += -g -fsanitize=address
endif

INCLUDES_DIR	:=	includes
INCLUDES	:=	-I./$(INCLUDES_DIR)/ -I$(LIBFT_DIR)/$(INCLUDES_DIR)/
ifeq ($(UNAME), Darwin)
	INCLUDES	+=	-I$(shell brew --prefix readline)/include
endif

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
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_all.py

# test multi pipe
.PHONY		: test_pipe
test_pipe	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_pipe.py

# test builtin cd
.PHONY		: test_cd
test_cd		: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_cd.py

# test builtin declare
.PHONY			: test_declare
test_declare	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_declare.py

# test builtin echo
.PHONY		: test_echo
test_echo	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_echo.py

# test builtin exit
.PHONY		: test_exit
test_exit	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_exit.py

# test builtin export
.PHONY		: test_export
test_export	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_export.py

# test builtin pwd
.PHONY		: test_pwd
test_pwd	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_pwd.py

# test op paren
.PHONY		: test_paren
test_paren	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_paren.py

# test op and or
.PHONY		: test_and_or
test_and_or	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_and_or.py

# test mix
.PHONY		: test_mix
test_mix	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_mix.py

# test redirects
.PHONY		: test_redirects
test_redirects	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_redirects.py

# test error
.PHONY		: test_error
test_error	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_error.py

# test env
.PHONY		: test_env
test_env	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_env.py

# test expansion
.PHONY		: test_expansion
test_expansion	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_expansion.py

# test original
.PHONY		: test_original
test_original	: all
	rm -f ko_case_*.txt
	python3 ./test/integration_test/run_original.py


-include $(DEPS)
