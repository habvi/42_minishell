#include "test.h"

t_ast_node	*node_new(t_node_kind kind, t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	printf("%s\n", __func__);
	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (node == NULL)
		error_exit(__func__, "failed to allocate");
	node->kind = kind;
	node->val = 0;
	node->left = left;
	node->right = right;
	return (node);
}

t_ast_node	*node_num_new(int val)
{
	t_ast_node	*node;

	printf("%s: %d\n", __func__, val);
	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (node == NULL)
		error_exit(__func__, "failed to allocate");
	node->kind = NODE_NUM;
	node->val = val;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
