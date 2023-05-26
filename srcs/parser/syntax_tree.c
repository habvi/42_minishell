#include "deque.h"
#include "parser.h"
#include "libft.h"

t_ast	*new_command_leaf(t_deque *cmd_head)
{
	t_ast	*new_leaf;

	new_leaf = (t_ast *) ft_calloc(1, sizeof(t_ast));
	if (!new_leaf)
		return (NULL);
	new_leaf->type = NODE_CMD;
	new_leaf->cmd_head = cmd_head;
	return (new_leaf);
}

t_ast	*new_node(t_type type, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}
