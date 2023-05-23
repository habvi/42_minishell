#include "test.h"

// BNF
//  expression	= term, [(+|-) term]*
//  term	    = primary, [(*|/) primary]*
//  primary     = num | '(' expr ')'
//  variable
//  digit

// [ref] https://www.sigbus.info/compilerbook
//       https://qiita.com/nomunomu0504/items/26c02aa4a5311ddcf856#%E8%A1%A8%E7%A4%BA%E9%96%A2%E6%95%B0

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

void	free_tree(t_tree *tree)
{
	(void)tree;
}

void	print_tree(t_tree *tree)
{
	(void)tree;
}

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
	t_tree		*lhs = term(token);
	t_tree		*node;
	t_node_kind	kind;

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
		node = new_node(kind, lhs, term(token));
		lhs = node;
	}
	return (node);
}

// term = primary, [(*|/) primary]*
t_tree	*term(t_token **token)
{
	t_tree		*lhs = primary(token);
	t_tree		*node;
	t_node_kind	kind;

	while (*token && is_kind_mul_or_div((*token)->kind))
	{
		kind = (*token)->kind;
		*token = (*token)->next;
		node = new_node(kind, lhs, primary(token));
		lhs = node;
	}
	return (node);
}

// primary = num | '(' expr ')'
t_tree	*primary(t_token **token)
{
	t_tree		*node;

	if (!token || !*token)
		return (NULL);
	if ((*token)->kind == nd_num)
	{
		node = new_num_leaf((*token)->val);
		return (node);
	}
	if ((*token)->kind == nd_left_paren)
	{
		*token = (*token)->next;
		node = expression(token);
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
