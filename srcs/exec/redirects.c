#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"

static bool	is_ambiguous_redirect(t_redirect *redirect)
{
	if (redirect->kind == TOKEN_KIND_REDIRECT_HEREDOC)
		return (false);
	return (redirect->tokens->size != 1);
}

static t_result	exec_redirect_each(t_redirect *redirect, int proc_fd[2])
{
	t_result	result;

	if (is_ambiguous_redirect(redirect))
	{
		puterr_cmd_msg("tmp", ERROR_MSG_AMBIGUOUS_REDIRECT); // todo: origin arg
		return (FAILURE);
	}
	result = open_redirect_fd_and_save_to_proc(redirect, proc_fd);
	return (result);
}

// OK [redirect_symbol]-[file]
// NG [redirect_symbol]-[redirect_symbol]: dropped $var
//    [redirect_symbol]-[file]-[file]    : splitted $var
t_result	exec_redirect_all(t_ast *self_node, t_context *context)
{
	t_deque_node	*node;
	t_result		result;

	if (!self_node->redirect_list)
		return (SUCCESS); //todo
	node = self_node->redirect_list->node;
	while (node)
	{
		result = exec_redirect_each(node->content, self_node->proc_fd);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (result == FAILURE)
		{
			context->status = 1; // todo: macro
			return (FAILURE);
		}
		node = node->next;
	}
	return (SUCCESS);
}

t_result	redirect_fd(t_ast *self_node, t_context *context)
{
	t_result	result;

	if (!self_node->redirect_list)
		return (SUCCESS);
	result = exec_redirect_all(self_node, context);
	if (result == FAILURE || result == PROCESS_ERROR)
		return (result);
	result = connect_redirect_to_proc(self_node);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
