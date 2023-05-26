#include "parser.h"

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
