#ifndef MS_EXPANSION_H
# define MS_EXPANSION_H

# include "ms_result.h"

# define CHAR_DOLLAR	'$'
# define STR_DOLLAR		"$"
# define STR_UNDERSCORE	"_"
# define PARAM_STATUS	'?'

typedef struct s_ast		t_ast;
typedef struct s_context	t_context;
// typedef struct s_deque		t_deque;
// typedef struct s_deque_node	t_deque_node;

t_result	expand_variables(t_ast *self_node, t_context *context);
char		*expand_parameter(char **str, t_context *context);
char		*substr_before_dollar(char **str);

#endif //MS_EXPANSION_H
