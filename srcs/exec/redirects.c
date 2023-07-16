#include <string.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"

static bool	is_ambiguous_redirect(t_redirect *redirect)
{
	if (redirect->kind == TOKEN_KIND_REDIRECT_HEREDOC)
		return (false);
	return (redirect->tokens->size != 1);
}

static t_result	exec_redirect_each(t_redirect *redirect, \
									int proc_fd[2], \
									t_context *context)
{
	t_result	result;
	char		*original_token;
	int			open_errno;
	char		*path;

	original_token = x_ft_strdup(get_head_token_str(redirect->tokens));
	expand_processing(&redirect->tokens, context);
	split_expand_word(&redirect->tokens);
	if (is_ambiguous_redirect(redirect))
	{
		context->status = STATUS_REDIRECT_FAILURE;
		puterr_cmd_msg(original_token, ERROR_MSG_AMBIGUOUS);
		ft_free(&original_token);
		return (FAILURE);
	}
	ft_free(&original_token);
	result = open_redirect_fd_and_save_to_proc(redirect, proc_fd, &open_errno);
	if (result == FAILURE)
	{
		context->status = STATUS_REDIRECT_FAILURE;
		path = get_head_token_str(redirect->tokens);
		puterr_cmd_msg(path, strerror(open_errno));
	}
	return (result);
}

// OK [redirect_symbol]-[file]
// NG [redirect_symbol]-[redirect_symbol]: dropped $var
//    [redirect_symbol]-[file]-[file]    : splitted $var

// redirect_list != NULL
static t_result	expand_and_exec_redirect_all(t_ast *self_node, \
												t_context *context)
{
	t_deque_node	*node;
	t_result		result;
	t_redirect		*redirect;

	node = self_node->redirect_list->node;
	while (node)
	{
		redirect = (t_redirect *)node->content;
		if (redirect->kind == TOKEN_KIND_REDIRECT_HEREDOC)
		{
			if (expand_for_heredoc(redirect, context) == PROCESS_ERROR)
				return (PROCESS_ERROR);
		}
		result = exec_redirect_each(node->content, self_node->proc_fd, context);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (result == FAILURE)
			return (FAILURE);
		node = node->next;
	}
	return (SUCCESS);
}

t_result	redirect_fd(t_ast *self_node, t_context *context)
{
	t_result	result;

	if (!self_node->redirect_list)
		return (SUCCESS);
	result = expand_and_exec_redirect_all(self_node, context);
	if (result == FAILURE || result == PROCESS_ERROR)
		return (result);
	result = connect_redirect_to_proc(self_node);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
