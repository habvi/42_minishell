#include "parser.h"
#include "deque.h"

// expr = mul ("+" mul | "-" mul)*
// mul = primary ("*" primary | "/" primary)*
// primary = num | "(" expr ")"
t_node	*primary(t_deque *token)
{
	t_node	*node;

	if (next_token_bool(token, '('))
	{
		node = expr(token);

		return (node);
	}
	return (node_num_new(next_token_val(token)));
}

t_node	*mul(t_deque *token)
{
	t_node	*node;

	node = primary(token);
	while (true)
	{
		if (next_token_bool(token, '*'))
			node = node_new(NODE_MUL, node, primary(token));
		else if (next_token_bool(token, '/'))
			node = node_new(NODE_DIV, node, primary(token));
		else
			return (node);
	}
}

t_node	*expr(t_deque *token)
{
	t_node	*node;

	node = mul(token);
	while (true)
	{
		if (next_token_bool(token, '+'))
			node = node_new(NODE_ADD, node, mul(token));
		else if (next_token_bool(token, '-'))
			node = node_new(NODE_SUB, node, mul(token));
		else
			return (node);
	}
}
