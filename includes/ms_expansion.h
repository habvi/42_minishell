#ifndef MS_EXPANSION_H
# define MS_EXPANSION_H

# include <stdbool.h>
# include "ms_result.h"

# define CHAR_DOLLAR	'$'
# define STR_DOLLAR		"$"
# define STR_UNDERSCORE	"_"
# define PARAM_STATUS	'?'
# define CURRENT_DIR	"."

typedef struct s_ast		t_ast;
typedef struct s_context	t_context;
typedef struct s_deque		t_deque;
// typedef struct s_deque_node	t_deque_node;

t_result	expand_variables(t_ast *self_node, t_context *context);
char		*expand_parameter(char **str, t_context *context);
char		*substr_before_dollar(char **str);
void		remove_empty_tokens(t_deque *tokens);
void		concat_tokens(t_deque *tokens);
void		split_expand_word(t_deque **tokens);
void		word_split_and_add(char *token_str, \
								t_deque *expanded, \
								bool concat_next);
void		expand_wildcard(t_deque **tokens);
t_deque		*get_pattern_matched_filenames(const char *token_str);
bool		is_pattern_match_target_path(const char *match_str, \
											const char *target_path);

#endif //MS_EXPANSION_H
