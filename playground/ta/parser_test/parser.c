#include "test.h"

// BNF
//  expression	= term, [(+|-) term]*
//  term	    = primary, [(*|/) primary]*
//  primary     = num | '(' expr ')'
//  variable
//  digit

// [ref] https://www.sigbus.info/compilerbook
//       https://qiita.com/nomunomu0504/items/26c02aa4a5311ddcf856#%E8%A1%A8%E7%A4%BA%E9%96%A2%E6%95%B0

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

//            ' '
// depth - 2 : │   (max_depth - 1)
// depth - 1 : └─

//[+]
// └─[*]
// │  └─ 1
// │  └─ 2
// └─[*]
//    └─[*]
//    │  └─ 3
//    │  └─ 4
//    └─ 5

// depth
// 0
//[-] 1
// ├─[+] 2
// │  ├─[+] 3
// │  │  ├─[+] 4  5
// │  │  │  └─[*]
// │  │  │  │  └─ 1
// │  │  │  │  └─ 2
// │  │  │  └─[*]
// │  │  │     └─ 3
// │  │  │     └─ 4
// │  │  └─ 5
// │  └─ 6
// └─[*]
//    └─ 7
//    └─ 8


// 0  1  2  3  4  5
// │  │  │     └─ 3
//             ^ right

static void print_tree_node(t_tree *node, int depth, int is_rhs, char *prefix)
{
	prefix[depth * PRINT_WIDTH] = '\0';

	dprintf(STDERR_FILENO, "%s%s─", prefix, (is_rhs ? "└" : "├"));
	if (node->kind == nd_num)
		dprintf(STDERR_FILENO, " %d \n", node->val);
	else
		dprintf(STDERR_FILENO, "[%c]\n", get_operator_char(node));

	prefix[depth * PRINT_WIDTH] = is_rhs ? ' ' : '|';
	prefix[depth * PRINT_WIDTH + 1] = ' ';
	prefix[depth * PRINT_WIDTH + 2] = ' ';

	if (node->lhs != NULL)
		print_tree_node(node->lhs, depth + 1, node->rhs == NULL, prefix);
	if (node->rhs != NULL)
		print_tree_node(node->rhs, depth + 1, 1, prefix);
}

void print_tree(t_tree *root)
{
	char draw_prefix[MAX_DEPTH * PRINT_WIDTH + 1] = {0};

	dprintf(STDERR_FILENO, "%-12s:\n", "print_tree");
	print_tree_node(root, 0, 1, draw_prefix);
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
