#ifndef MS_EXPANSION_H
# define MS_EXPANSION_H

# include <stdbool.h>
# include <stddef.h>
# include <dirent.h>
# include "ms_result.h"

# define CHAR_DOLLAR	'$'
# define STR_DOLLAR		"$"
# define STR_UNDERSCORE	"_"
# define PARAM_STATUS	'?'
# define CURRENT_DIR	"."
# define HIDDEN_FILE	'.'
# define WILDCARD		'*'

# define ERROR_MSG_AMBIGUOUS		"ambiguous redirect"
# define STATUS_REDIRECT_FAILURE	1

typedef struct s_ast		t_ast;
typedef struct s_context	t_context;
typedef struct s_deque		t_deque;
typedef struct s_redirect	t_redirect;
typedef struct s_token		t_token;

t_result	expand_variable_of_cmd_tokens(t_ast *self_node, t_context *context);
t_result	expand_processing(t_deque **tokens, t_context *context);
char		*get_expand_token_str(char *str, t_context *context);
char		*substr_before_dollar(char **str);
void		remove_empty_tokens(t_deque *tokens);
void		concat_tokens(t_deque *tokens);
void		split_expand_word(t_deque **tokens);
void		word_split_and_add(char *token_str, \
								t_deque *expanded, \
								bool concat_next);
t_result	expand_wildcard(t_deque **tokens);
t_deque		*get_pattern_matched_filenames(const t_token *token, \
											t_result *result);
bool		is_pattern_match_target_path(const char *match_str, \
											const size_t len_match, \
											const char *target_path, \
											const bool *is_quoted_arr);
t_result	open_current_directory(DIR **dirp);
t_result	get_next_dirp_in_current(DIR *dirp, struct dirent **dirent);
t_result	close_current_directory(DIR *dirp);
void		sort_filenames(t_deque *tokens);
t_result	expand_for_heredoc(t_ast *self_node, t_context *context);
t_result	expand_variables_in_heredoc(t_redirect *redirect, \
										t_context *context);
t_result	expand_for_filename_each(t_redirect *redirect, t_context *context);
void		assign_failure_fd_to_proc_fds(int proc_fd[2]);

#endif //MS_EXPANSION_H
