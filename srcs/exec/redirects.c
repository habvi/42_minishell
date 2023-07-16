#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

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
	int			open_errno;
	char		*path;

	result = open_redirect_fd_and_save_to_proc(redirect, proc_fd, &open_errno);
	if (result == FAILURE)
	{
		context->status = STATUS_REDIRECT_FAILURE;
		path = get_head_token_str(redirect->tokens);
		puterr_cmd_msg(path, strerror(open_errno));
	}
	return (result);
}

static t_result	expand_for_redirect_file(t_redirect *redirect, \
										t_context *context)
{
	char		*original_token;
	t_result	result;

	original_token = x_ft_strdup(get_head_token_str(redirect->tokens));
	expand_processing(&redirect->tokens, context);
	split_expand_word(&redirect->tokens);
	result = is_ambiguous_redirect(redirect);
	if (result == FAILURE)
	{
		context->status = STATUS_REDIRECT_FAILURE;
		puterr_cmd_msg(original_token, ERROR_MSG_AMBIGUOUS);
	}
	ft_free(&original_token);
	return (result);
}

static t_result	expand_for_redirect(t_redirect *redirect, \
									t_context *context)
{
	if (redirect->kind == TOKEN_KIND_REDIRECT_HEREDOC)
	{
		if (expand_for_heredoc(redirect, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	else
	{
		if (expand_for_redirect_file(redirect, context) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
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
		result = expand_for_redirect(redirect, context);
		if (result == FAILURE || result == PROCESS_ERROR)
			return (result);
		result = exec_redirect_each(node->content, self_node->proc_fd, context);
		if (result == FAILURE || result == PROCESS_ERROR)
			return (result);
		node = node->next;
	}
	return (SUCCESS);
}

t_result	close_exit_fd(t_ast *self_node)
{
	const char	*command = get_head_token_str(self_node->command);

	if (!ft_streq(command, CMD_EXIT))
		return (SUCCESS);
	if (self_node->proc_fd[IN] != IN_FD_INIT)
	{
		if (x_close(self_node->proc_fd[IN]) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (self_node->proc_fd[OUT] != OUT_FD_INIT)
	{
		if (x_close(self_node->proc_fd[OUT]) == PROCESS_ERROR)
			return (PROCESS_ERROR);
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
	if (close_exit_fd(self_node) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
