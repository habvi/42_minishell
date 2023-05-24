#include "test.h"

void	print_split(char **split)
{
	size_t	i;

	i = 0;
	dprintf(STDERR_FILENO, "%-12s:[", "split");
	while (split && split[i])
	{
		dprintf(STDERR_FILENO, "%s", split[i]);
		i++;
		if (split[i])
			dprintf(STDERR_FILENO, ", ");
	}
	dprintf(STDERR_FILENO, "]\n");
}

void	print_token(t_token *token_head)
{
	t_token	*ptr;

	dprintf(STDERR_FILENO, "%-12s:[", "print_token");
	ptr = token_head;
	while (ptr)
	{
		if (ptr->kind == nd_num)
			dprintf(STDERR_FILENO, "%d", ptr->val);
		else if (ptr->kind == nd_add)
			dprintf(STDERR_FILENO, "+");
		else if (ptr->kind == nd_sub)
			dprintf(STDERR_FILENO, "-");
		else if (ptr->kind == nd_mul)
			dprintf(STDERR_FILENO, "*");
		else if (ptr->kind == nd_div)
			dprintf(STDERR_FILENO, "/");
		else if (ptr->kind == nd_left_paren)
			dprintf(STDERR_FILENO, "(");
		else if (ptr->kind == nd_right_paren)
			dprintf(STDERR_FILENO, ")");
		else
			dprintf(STDERR_FILENO, "(EOF)");
		ptr = ptr->next;
		if (ptr)
			dprintf(STDERR_FILENO, " ");
	}
	dprintf(STDERR_FILENO, "]\n");
}

void	print_token_node(t_token *token)
{
	dprintf(STDERR_FILENO, "print_tree_node:[");
	if (token && token->kind == nd_num)
		dprintf(STDERR_FILENO, "%d", token->val);
	else if (token && token->kind == nd_add)
		dprintf(STDERR_FILENO, "+");
	else if (token && token->kind == nd_sub)
		dprintf(STDERR_FILENO, "-");
	else if (token && token->kind == nd_mul)
		dprintf(STDERR_FILENO, "*");
	else if (token && token->kind == nd_div)
		dprintf(STDERR_FILENO, "/");
	else if (token && token->kind == nd_left_paren)
		dprintf(STDERR_FILENO, "(");
	else if (token && token->kind == nd_right_paren)
		dprintf(STDERR_FILENO, ")");
	else if (token)
		dprintf(STDERR_FILENO, "(EOF)");
	dprintf(STDERR_FILENO, "]\n");
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
