#include "test.h"

// BNF
//  expression	= term, [(+|-) term]*
//  term	    = primary, [(*|/) primary]*
//  primary     = num | '(' expr ')'
//  variable
//  digit

// [ref] https://www.sigbus.info/compilerbook
//       https://qiita.com/nomunomu0504/items/26c02aa4a5311ddcf856#%E8%A1%A8%E7%A4%BA%E9%96%A2%E6%95%B0
static bool	is_kind_add_or_sub(t_node_kind kind)
{
	return (kind == nd_add || kind == nd_sub);
}

static bool	is_kind_mul_or_div(t_node_kind kind)
{
	return (kind == nd_mul || kind == nd_div);
}

// expr = mul, [(+|-) mul]*
t_tree	*expression(t_token **token)
{
//	printf("\n%s 0\n", __func__);
//	print_token_node(*token);
	t_tree		*lhs = term(token);
	t_tree		*rhs;
	t_node_kind	kind;

//	printf("\n%s 1\n", __func__);
//	print_token_node(*token);

//	printf("lhs:%p\n", lhs);
//	printf("lhs->kind:%c\n", get_operator_char(lhs));
//	print_tree_node(lhs, 0, "lhs");

	//
	//         term(token)
	//            v     v new_node(next)
	// [1 + 2] = [1] + [2]
	//               ^
	//               now
	//          +
	//     ┌────┴────┐
	// term(lhs)   term(rhs)
	//     1         2
	//
	while (*token && is_kind_add_or_sub((*token)->kind))
	{
		kind = (*token)->kind;
		*token = (*token)->next;
		rhs = term(token);
		lhs = new_node(kind, lhs, rhs);
	}
	return (lhs);
}

// term = primary, [(*|/) primary]*
t_tree	*term(t_token **token)
{
//	printf("\n %s 1\n", __func__);
//	print_token_node(*token);

	t_tree		*lhs = primary(token);
	t_tree		*rhs;
	t_node_kind	kind;

//	printf("\n %s 2\n", __func__);
//	print_token_node(*token);

	while (*token && is_kind_mul_or_div((*token)->kind))
	{
		kind = (*token)->kind;
		*token = (*token)->next;
		rhs = primary(token);
		lhs = new_node(kind, lhs, rhs);
	}
	return (lhs);
}

// primary = num | '(' expr ')'
t_tree	*primary(t_token **token)
{
	t_tree		*node;

//	printf("\n  %s 1\n", __func__);
//	print_token_node(*token);

	if (!token || !*token)
		return (NULL);
	if ((*token)->kind == nd_num)
	{
//		printf("\n  %s 2\n", __func__);
//		print_token_node(*token);

		node = new_num_leaf((*token)->val);
		*token = (*token)->next;
		return (node);
	}
	if ((*token)->kind == nd_left_paren)
	{
//		printf("\n  %s 3\n", __func__);
//		print_token_node(*token);

		*token = (*token)->next;
		node = expression(token); // kind=( or )
		if ((*token)->kind == nd_right_paren)
		{
			*token = (*token)->next;
			return (node);
		}
		dprintf(STDERR_FILENO, "error\n");
		return (NULL);
	}
	dprintf(STDERR_FILENO, "error\n");
	return (NULL);
}
