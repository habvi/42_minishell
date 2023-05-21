#include "test.h"

// BNF
//  expr    = mul ("+" mul | "-" mul)*
//  mul     = primary ("*" primary | "/" primary)*
//  primary = num | "(" expr ")"

// [ref] https://www.sigbus.info/compilerbook

t_tree	*new_node(t_node_kind kind, t_tree *lhs, t_tree *rhs)
{
	t_tree	*node;

	node = calloc(sizeof(t_tree), 1);
	node->kind = kind;
	node->lhs = lhs;
	node->rhs = rhs;
	return (node);
}

t_tree	*new_node_num(int val)
{
	t_tree	*node;

	node = calloc(sizeof(t_tree), 1);
	node->kind = nd_num;
	node->val = val;
	return (node);
}

//t_tree	*expr(t_token *token)
//{
//
//}


