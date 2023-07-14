#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_hash.h"

static t_result	execute_heredoc_all(t_deque *redirect_list)
{
	t_deque_node	*redirect_node;
	t_result		result;
	t_redirect		*redirect;

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
		result = execute_heredoc_each(redirect);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		redirect_node = redirect_node->next;
	}
	return (SUCCESS);
}

t_result	execute_heredoc(t_ast *ast_node)
{
	t_result	heredoc_result;
	t_result	left_result;
	t_result	right_result;

	if (!ast_node)
		return (SUCCESS);
	left_result = execute_heredoc(ast_node->left);
	if (left_result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	right_result = execute_heredoc(ast_node->right);
	if (right_result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (!is_node_kind_exec_heredoc(ast_node->kind))
		return (SUCCESS);
	move_redirect_from_command(ast_node);
	heredoc_result = execute_heredoc_all(ast_node->redirect_list);
	if (heredoc_result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
