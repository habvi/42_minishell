#include "test.h"

// expr = mul ("+" mul | "-" mul)*
// mul = primary ("*" primary | "/" primary)*
// primary = num | "(" expr ")"
t_token	*primary(t_token *token)
{
	t_token	*token;

	if (next_token_bool(token, '('))
	{
		token = expr(token);

		return (token);
	}
	return (node_num_new(next_token_val(token)));
}

t_token	*mul(t_token *token)
{
	t_token	*token;

	token = primary(token);
	while (true)
	{
		if (next_token_bool(token, '*'))
			token = node_new(NODE_MUL, token, primary(token));
		else if (next_token_bool(token, '/'))
			token = node_new(NODE_DIV, token, primary(token));
		else
			return (token);
	}
}

t_token	*expr(t_token *token)
{
	t_token	*token;

	token = mul(token);
	while (true)
	{
		if (next_token_bool(token, '+'))
			token = node_new(NODE_ADD, token, mul(token));
		else if (next_token_bool(token, '-'))
			token = node_new(NODE_SUB, token, mul(token));
		else
			return (token);
	}
}

t_token	*parse(t_token *token)
{
	return (expr(token));
}
