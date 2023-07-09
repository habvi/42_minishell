#ifndef MS_EXPANSION_H
# define MS_EXPANSION_H

# include "ms_result.h"

typedef struct s_ast		t_ast;
typedef struct s_context	t_context;
// typedef struct s_deque		t_deque;
// typedef struct s_deque_node	t_deque_node;

t_result	expand_variables(t_ast *self_node, t_context *context);

#endif //MS_EXPANSION_H
