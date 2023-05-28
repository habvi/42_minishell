#include "test.h"
#include "libft.h"

static bool	next_token_bool(t_token **token, char *op)
{
	if (is_equal_strings((*token)->str, op))
	{
		*token = (*token)->next;
		return (true);
	}
	return (false);
}

static int	next_token_val(t_token **token)
{
	const int	val = (*token)->val;

	if ((*token)->kind != NODE_NUM)
		error_exit(__func__, "not num");
	*token = (*token)->next;
	return (val);
}

// expr = mul ("+" mul | "-" mul)*
// mul = primary ("*" primary | "/" primary)*
// primary = num | "(" expr ")"
t_ast_node	*primary(t_token **token)
{
	t_ast_node	*node;
	char		*str;

	str = (*token)->str;
	if (next_token_bool(token, "("))
	{
		node = expr(token);
		return (node);
	}
	return (node_num_new(next_token_val(token)));
}

t_ast_node	*mul(t_token **token)
{
	t_ast_node	*node;
	char		*str;

	node = primary(token);
	while (*token)
	{
		str = (*token)->str;
		if (next_token_bool(token, "*"))
			node = node_new(NODE_MUL, node, primary(token));
		else if (next_token_bool(token, "/"))
			node = node_new(NODE_DIV, node, primary(token));
		else
			return (node);
	}
	return (NULL);
}

t_ast_node	*expr(t_token **token)
{
	t_ast_node	*node;
	char		*str;

	node = mul(token);
	while (*token)
	{
		str = (*token)->str;
		if (next_token_bool(token, "+"))
			node = node_new(NODE_ADD, node, mul(token));
		else if (next_token_bool(token, "-"))
			node = node_new(NODE_SUB, node, mul(token));
		else
			return (node);
	}
	return (NULL);
}

t_ast_node	*create_ast(t_token *token)
{
	return (expr(&token));
}
