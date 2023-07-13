#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_mem.h"

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
		ft_dprintf(STDERR_FILENO, "%s", token->str);
		node = node->next;
		if (node)
			ft_dprintf(STDERR_FILENO, " ");
	}
}

static void	print_redirect_in_oneline(t_deque *dq)
{
	t_deque_node	*node;
	t_redirect		*redirect;

	node = dq->node;
	while (node)
	{
		redirect = (t_redirect *)node->content;
		ft_dprintf(STDERR_FILENO, "%s ", get_token_kind_str(redirect->kind));
		print_tokens_dq_in_oneline(redirect->tokens);
		node = node->next;
		if (node)
			ft_dprintf(STDERR_FILENO, " ");
	}
}

static void	print_token_comamnd_and_redirect(t_ast *ast)
{
	if (ast->command)
	{
		ft_dprintf(STDERR_FILENO, "command[");
		print_tokens_dq_in_oneline(ast->command);
		ft_dprintf(STDERR_FILENO, "]");
	}
	if (ast->redirect_list)
	{
		ft_dprintf(STDERR_FILENO, ", redirect[");
		print_redirect_in_oneline(ast->redirect_list);
		ft_dprintf(STDERR_FILENO, "], ");
	}
	ft_dprintf(STDERR_FILENO, "fd: prev[%d]in[%d]out[%d] ", \
				ast->prev_fd, ast->pipe_fd[READ], ast->pipe_fd[WRITE]);
	ft_dprintf(STDERR_FILENO, "\n");
}

static void	print_tree_node(t_ast *node, int depth, int is_rhs, char *prefix)
{
	if (!node)
		return ;
	prefix[depth * PRINT_WIDTH] = '\0';
	ft_dprintf(STDERR_FILENO, "%s%s─", prefix, get_tree_symbol(is_rhs));
	if (node->kind == NODE_KIND_COMMAND && node->command)
		print_token_comamnd_and_redirect(node);
	else if (node->kind == NODE_KIND_SUBSHELL)
	{
		ft_dprintf(STDERR_FILENO, "( ) ");
		print_token_comamnd_and_redirect(node);
	}
	else if (node->kind == NODE_KIND_OP_PIPE)
	{
		ft_dprintf(STDERR_FILENO, "[|] ");
		print_token_comamnd_and_redirect(node);
	}
	else
		ft_dprintf(STDERR_FILENO, "[%s]\n", get_ast_node_kind_str(node->kind));
	prefix[depth * PRINT_WIDTH] = get_tree_space(is_rhs);
	prefix[depth * PRINT_WIDTH + 1] = ' ';
	prefix[depth * PRINT_WIDTH + 2] = ' ';
	if (node->left != NULL)
		print_tree_node(node->left, depth + 1, node->right == NULL, prefix);
	if (node->right != NULL)
		print_tree_node(node->right, depth + 1, 1, prefix);
}

void	debug_print_ast_tree(t_ast *root, const char *str)
{
	char	draw_prefix[MAX_DEPTH * PRINT_WIDTH + 1];

	ft_bzero(draw_prefix, MAX_DEPTH * PRINT_WIDTH + 1);
	ft_dprintf(STDERR_FILENO, "-------------------------\n");
	ft_dprintf(STDERR_FILENO, "%-12s\n", str);
	print_tree_node(root, 0, 1, draw_prefix);
	ft_dprintf(STDERR_FILENO, "-------------------------\n");
}
