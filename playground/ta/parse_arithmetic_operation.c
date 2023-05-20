#include "test.h"

// BNF
//  expr    = mul ("+" mul | "-" mul)*
//  mul     = primary ("*" primary | "/" primary)*
//  primary = num | "(" expr ")"

// [ref] https://www.sigbus.info/compilerbook

t_node	*new_node(t_node_kind kind, t_node *lhs, t_node *rhs)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	node->kind = kind;
	node->lhs = lhs;
	node->rhs = rhs;
	return (node);
}

t_node	*new_node_num(int val)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	node->kind = nd_num;
	node->val = val;
	return (node);
}

//t_node	*expr()
//{
//
//}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage               : $ ./a.out \"numerical formula\"\n"
			   "available operators : +, -, *, /, (, )\n");
		return (1);
	}
	printf("%s\n", argv[1]);
	return (0);
}
