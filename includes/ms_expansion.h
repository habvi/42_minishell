#ifndef MS_EXPANSION_H
# define MS_EXPANSION_H

# include <stdbool.h>
# include <stddef.h>
# include "ms_result.h"

# define CHAR_DOLLAR	'$'
# define STR_DOLLAR		"$"
# define STR_UNDERSCORE	"_"
# define PARAM_STATUS	'?'
# define CURRENT_DIR	"."
# define HIDDEN_FILE	'.'
# define WILDCARD		'*'
# define ASSIGN_SYMBOL	'='

# define IS_QUOTED		(true)

typedef struct s_ast		t_ast;
typedef struct s_context	t_context;
typedef struct s_deque		t_deque;
typedef struct s_redirect	t_redirect;
typedef struct s_token		t_token;

t_result	expand_variables(t_ast *self_node, t_context *context);
char		*get_expand_token_str(char *str, t_context *context);
char		*substr_before_dollar(char **str);
void		remove_empty_tokens(t_deque *tokens);
void		concat_tokens(t_deque *tokens);
void		split_expand_word(t_deque **tokens);
void		word_split_and_add(char *token_str, \
								t_deque *expanded, \
								bool concat_next);
void		expand_wildcard(t_deque **tokens);
t_deque		*get_pattern_matched_filenames(t_token *token);
bool		is_pattern_match_target_path(const char *match_str, \
											const size_t len_match, \
											const char *target_path, \
											const bool *is_quoted_arr);
void		sort_filenames(t_deque *tokens);
t_result	expand_for_heredoc(t_redirect *redirect, t_context *context);
t_result	expand_variables_in_heredoc(t_redirect *redirect, \
										t_context *context);
void		update_is_quoted_arr_for_wildcard(t_deque *tokens);

#endif //MS_EXPANSION_H
