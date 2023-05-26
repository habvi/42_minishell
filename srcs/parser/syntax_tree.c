#include "deque.h"
#include "parser.h"
#include "libft.h"
#include "ft_dprintf.h"
#include "tokenize.h"

t_ast	*new_command_leaf(t_deque *cmd_head)
{
	t_ast	*new_leaf;

	new_leaf = (t_ast *) ft_calloc(1, sizeof(t_ast));
	if (!new_leaf)
		return (NULL);
	new_leaf->type = NODE_CMD;
	new_leaf->cmd_head = cmd_head;
	new_leaf->left = NULL;
	new_leaf->right = NULL;
	return (new_leaf);
}

t_ast	*new_node(t_type type, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->cmd_head = NULL;
	new_node->type = type;
	new_node->left = left;
	new_node->right = right;
	if (left)
		left->parent = new_node;
	if (right)
		right->parent = new_node;
	return (new_node);
}

// free tree
void	ast_clear(t_ast **root)
{
	//todo free tree
	*root = NULL;
}

void	print_cmds(t_ast *cmd_node)
{
	t_deque_node	*node;

	ft_dprintf(STDERR_FILENO, " cmd:[");
	node = cmd_node->cmd_head->node;
	while (node)
	{
		ft_dprintf(STDERR_FILENO, "%s", (char *)node->content);
		node = node->next;
		if (node)
			ft_dprintf(STDERR_FILENO, ", ");
	}
	ft_dprintf(STDERR_FILENO, "]\n");
}

void	print_ast(t_ast *ast_node)
{
	if (!ast_node)
		return ;
	if (ast_node->type == NODE_CMD)
		print_cmds(ast_node);
	else if (ast_node->type == NODE_PIPE)
	{
		print_ast(ast_node->left);
		ft_dprintf(STDERR_FILENO, "  pipe\n");
		print_ast(ast_node->right);
	}
}