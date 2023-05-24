#include "test.h"

size_t	max_size(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

t_tree	*new_node(t_node_kind kind, t_tree *lhs, t_tree *rhs)
{
	t_tree	*node;

	node = calloc(sizeof(t_tree), 1);
	node->kind = kind;
	node->lhs = lhs;
	node->rhs = rhs;
	return (node);
}

t_tree	*new_num_leaf(int val)
{
	t_tree	*node;

	node = calloc(sizeof(t_tree), 1);
	node->kind = nd_num;
	node->val = val;
	return (node);
}

void	free_tree(t_tree **node)
{
	if (!node || !*node)
		return ;
	free_tree(&(*node)->lhs);
	free_tree(&(*node)->rhs);
	(*node)->lhs = NULL;
	(*node)->rhs = NULL;
	free(*node);
	*node = NULL;
}

char	get_operator_char(t_tree *node)
{
	if (node->kind == nd_add)
		return ('+');
	if (node->kind == nd_sub)
		return ('-');
	if (node->kind == nd_mul)
		return ('*');
	if (node->kind == nd_div)
		return ('/');
	if (node->kind == nd_left_paren)
		return ('(');
	if (node->kind == nd_right_paren)
		return (')');
	return ('.');
}

size_t	get_depth(t_tree *node)
{
	size_t	left;
	size_t	right;

	if (!node)
		return (0);
	left = get_depth(node->lhs);
	right = get_depth(node->rhs);
	return (max_size(left, right) + 1);
}
