#include "minishell.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_sys.h"

static t_ast	*init_ast_node(void)
{
	t_ast	*new_node;

	new_node = (t_ast *)x_malloc(sizeof(t_ast));
	if (!new_node)
		ft_abort();
	new_node->kind = NODE_KIND_NONE;
	new_node->command = NULL;
	new_node->redirects = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_ast	*new_command_leaf(void)
{
	t_ast	*new_node;

	new_node = init_ast_node();
	new_node->kind = NODE_KIND_COMMAND;
	new_node->command = deque_new();
	if (!new_node->command)
		ft_abort();
	return (new_node);
}

t_ast	*new_ast_node(t_node_kind kind, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	new_node = init_ast_node();
	new_node->kind = kind;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}
