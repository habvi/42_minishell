#include <stdlib.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

// todo: norm error this file

// gcc srcs/tokenize/*.c srcs/parse/*.c srcs/utils/*.c srcs/builtin/*.c srcs/variables/*.c  libft/libft.a -Iincludes -Ilibft/includes && ./a.out

#define MAX_DEPTH	100
#define PRINT_WIDTH	3

static void	print_tokens_dq_in_oneline(t_deque *dq)
{
	t_deque_node	*node;
	t_token			*token;

	node = dq->node;
	while (node)
	{
		token = (t_token *)node->content;
		ft_dprintf(STDERR_FILENO, "%s ", token->str);
		node = node->next;
	}
	ft_dprintf(STDERR_FILENO, "\n");
}

static char	*get_ast_node_kind_str(t_node_kind node_kind)
{
	if (node_kind == NODE_KIND_OP_PIPE)
		return ("|");
	if (node_kind == NODE_KIND_OP_OR)
		return ("||");
	if (node_kind == NODE_KIND_OP_AND)
		return ("&&");
	if (node_kind == NODE_KIND_SUBSHELL)
		return ("(");
	return ("");
}

static void	print_tree_node(t_ast *node, int depth, int is_rhs, char *prefix)
{
	if (!node)
		return ;
	prefix[depth * PRINT_WIDTH] = '\0';
	ft_dprintf(STDERR_FILENO, "%s%s─", prefix, (is_rhs ? "└" : "├"));
	if (node->kind == NODE_KIND_COMMAND && node->command)
		print_tokens_dq_in_oneline(node->command);
	else if (node->kind == NODE_KIND_SUBSHELL)
		ft_dprintf(STDERR_FILENO, "( )\n");
	else
		ft_dprintf(STDERR_FILENO, "[%s]\n", get_ast_node_kind_str(node->kind));
	prefix[depth * PRINT_WIDTH] = is_rhs ? ' ' : '|';
	prefix[depth * PRINT_WIDTH + 1] = ' ';
	prefix[depth * PRINT_WIDTH + 2] = ' ';
	if (node->left != NULL)
		print_tree_node(node->left, depth + 1, node->right == NULL, prefix);
	if (node->right != NULL)
		print_tree_node(node->right, depth + 1, 1, prefix);
}

void	debug_print_ast_tree(t_ast *root, const char *str)
{
	char draw_prefix[MAX_DEPTH * PRINT_WIDTH + 1] = {0};

	ft_dprintf(STDERR_FILENO, "-------------------------\n");
	ft_dprintf(STDERR_FILENO, "%-12s:\n", str);
	print_tree_node(root, 0, 1, draw_prefix);
	ft_dprintf(STDERR_FILENO, "-------------------------\n");
}

// int main()
// {
// 	t_ast node1, node2, node3, node4, node5, node6, node7, node8, node9;
// 	t_deque *tokens;

// 	node1.kind = NODE_KIND_COMMAND;
// 	node1.command = deque_new();
// 	tokens = tokenize_line("echo a");
// 	deque_add_back(node1.command, tokens->node);
// 	free(tokens);
// 	node1.redirects = NULL;
// 	node1.left = NULL;
// 	node1.right = NULL;

// 	node2.kind = NODE_KIND_OP_PIPE;
// 	node2.command = NULL;
// 	node2.redirects = NULL;
// 	node2.left = &node1;
// 	node2.right = &node3;

// 	node3.kind = NODE_KIND_COMMAND;
// 	node3.command = deque_new();
// 	tokens = tokenize_line("echo b");
// 	deque_add_back(node3.command, tokens->node);
// 	free(tokens);
// 	node3.redirects = NULL;
// 	node3.left = NULL;
// 	node3.right = NULL;

// 	node4.kind = NODE_KIND_OP_AND;
// 	node4.command = deque_new();
// 	tokens = tokenize_line("&&");
// 	deque_add_back(node4.command, tokens->node);
// 	free(tokens);
// 	node4.redirects = NULL;
// 	node4.left = &node2;
// 	node4.right = &node8;

// 	node5.kind = NODE_KIND_COMMAND;
// 	node5.command = deque_new();
// 	tokens = tokenize_line("echo c");
// 	deque_add_back(node5.command, tokens->node);
// 	free(tokens);
// 	node5.redirects = NULL;
// 	node5.left = NULL;
// 	node5.right = NULL;

// 	node6.kind = NODE_KIND_OP_PIPE;
// 	node6.command = NULL;
// 	node6.redirects = NULL;
// 	node6.left = &node5;
// 	node6.right = &node7;

// 	node7.kind = NODE_KIND_COMMAND;
// 	node7.command = deque_new();
// 	tokens = tokenize_line("echo d");
// 	deque_add_back(node7.command, tokens->node);
// 	free(tokens);
// 	node7.redirects = NULL;
// 	node7.left = NULL;
// 	node7.right = NULL;

// 	node8.kind = NODE_KIND_OP_OR;
// 	node8.command = deque_new();
// 	tokens = tokenize_line("||");
// 	deque_add_back(node8.command, tokens->node);
// 	free(tokens);
// 	node8.redirects = NULL;
// 	node8.left = &node6;
// 	node8.right = &node9;

// 	node9.kind = NODE_KIND_COMMAND;
// 	node9.command = deque_new();
// 	tokens = tokenize_line("echo e");
// 	deque_add_back(node9.command, tokens->node);
// 	free(tokens);
// 	node9.redirects = NULL;
// 	node9.left = NULL;
// 	node9.right = NULL;

// 	debug_print_ast_tree(&node4, "main");

// 	return 0;
// }
