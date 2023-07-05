#ifndef MS_PARSE_H
# define MS_PARSE_H

# include <stdbool.h>

typedef struct s_context	t_context;
typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;
typedef struct s_token		t_token;
typedef struct s_ast		t_ast;

typedef enum e_node_kind
{
	NODE_KIND_COMMAND,
	NODE_KIND_OP_PIPE,
	NODE_KIND_OP_OR,
	NODE_KIND_OP_AND,
	NODE_KIND_PAREN_LEFT,
	NODE_KIND_PAREN_RIGHT,
}	t_node_kind;

typedef struct s_redirect
{
	t_deque	*list;
	int		in_fd;
	int		out_fd;
}	t_redirect;

struct s_ast
{
	t_node_kind	kind;
	t_deque		*command;
	t_redirect	*redirects;
	t_ast		*left;
	t_ast		*right;
};

t_ast	*parse(t_deque *tokens, t_context *context);

/* syntax check */
bool	is_parenthesis_concatenated_all(t_deque_node *node);

#endif //MS_PARSE_H
