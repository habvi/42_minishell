#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_hash.h"

static t_result	execute_heredoc_all(t_deque *redirect_list, \
									bool is_interactive, \
									bool is_test)
{
	t_deque_node	*redirect_node;
	t_redirect		*redirect;
	t_result		heredoc_result;

	if (!redirect_list)
		return (SUCCESS);
	redirect_node = redirect_list->node;
	while (redirect_node)
	{
		redirect = (t_redirect *)redirect_node->content;
		if (redirect->kind != TOKEN_KIND_REDIRECT_HEREDOC)
		{
			redirect_node = redirect_node->next;
			continue ;
		}
		heredoc_result = execute_heredoc_each(\
										redirect, is_interactive, is_test);
		if (heredoc_result == BREAK || heredoc_result == PROCESS_ERROR)
			return (heredoc_result);
		redirect_node = redirect_node->next;
	}
	return (SUCCESS);
}

// heredoc interrupted by SIGINT, heredoc_result is BREAK
t_result	execute_heredoc(t_ast *ast_node, bool is_interactive, bool is_test)
{
	t_result	left_result;
	t_result	right_result;
	t_result	heredoc_result;

	if (!ast_node)
		return (SUCCESS);
	left_result = execute_heredoc(ast_node->left, is_interactive, is_test);
	if (left_result == BREAK || left_result == PROCESS_ERROR)
		return (left_result);
	right_result = execute_heredoc(ast_node->right, is_interactive, is_test);
	if (right_result == BREAK || right_result == PROCESS_ERROR)
		return (right_result);
	if (!is_node_kind_exec_heredoc(ast_node->kind))
		return (SUCCESS);
	move_redirect_from_command(ast_node);
	heredoc_result = execute_heredoc_all(\
							ast_node->redirect_list, is_interactive, is_test);
	if (heredoc_result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (heredoc_result);
}
