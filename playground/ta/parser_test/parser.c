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

void	print_tree_node(t_tree *node, int depth, char *str)
{
	int	i = 0;

	if (!node)
		return ;
	printf("%20s : ", str);
	while (i < depth)
	{
		printf(" ");
		i++;
	}
	if (node->kind == nd_num)
		printf("num:%d\n", node->val);
	else
		printf("ope:%c\n", get_operator_char(node));
}

void	free_tree(t_tree *tree)
{
	(void)tree;
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

//void print_tree_node(t_tree *node, int depth)
//{
//	int	i;
//
//	i = 0;
//	while (i < depth)
//	{
//		printf("  ");
//		i++;
//	}
//	if (node->kind == nd_num) {
//		printf("%d\n", node->val);
//	}
//	else {
//		printf("%c\n", get_operator_char(node));
//		if (node->lhs != NULL) {
//			print_tree_node(node->lhs, depth + 1);
//		}
//		if (node->rhs != NULL) {
//			print_tree_node(node->rhs, depth + 1);
//		}
//	}
//}
//
//void print_tree(t_tree *root) {
//	print_tree_node(root, 0);
//}

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
//		printf("\n%s 2\n", __func__);
//		print_token_node(*token);

		kind = (*token)->kind;
		*token = (*token)->next;

//		printf("\n%s 3\n", __func__);
//		print_token_node(*token);

		rhs = term(token);
		lhs = new_node(kind, lhs, rhs);

//		printf("\n%s 4\n", __func__);
//		print_token_node(*token);

	}
//	printf("\n%s 5\n", __func__);
//	print_token_node(*token);

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
//		printf("\n %s 3\n", __func__);
//		print_token_node(*token);

		kind = (*token)->kind;
		*token = (*token)->next;
//		printf("\n %s 4\n", __func__);
//		print_token_node(*token);

		rhs = primary(token);
		lhs = new_node(kind, lhs, rhs);

//		printf("\n %s 5\n", __func__);
//		print_token_node(*token);

	}
	printf("\n %s 6\n", __func__);
	print_token_node(*token);

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
