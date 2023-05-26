#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
void	error_exit(const char *func_name, const char *msg)
{
	dprintf(STDERR_FILENO, "Error(%s): %s\n", func_name, msg);
	exit(EXIT_FAILURE);
}

t_node	*node_new(t_node_kind kind, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->kind = kind;
	node->left = left;
	node->right = right;
	node->val = 0;
	return (node);
}

t_node	*node_num_new(int val)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->kind = NODE_NUM;
	node->left = NULL;
	node->right = NULL;
	node->val = val;
	return (node);
}

int	main(void)
{
	return (0);
}
