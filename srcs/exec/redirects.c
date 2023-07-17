#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_string.h"
#include "ft_sys.h"

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

t_result	close_prod_fd_for_exit_command(t_ast *self_node)
{
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
	const char	*command = get_head_token_str(self_node->command);
	t_result	result;

	if (!self_node->redirect_list)
		return (SUCCESS);
	result = expand_and_exec_redirect_all(self_node, context);
	if (result == FAILURE || result == PROCESS_ERROR)
		return (result);
	if (ft_streq(command, CMD_EXIT))
	{
		if (close_prod_fd_for_exit_command(self_node) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		return (SUCCESS);
	}
	result = connect_redirect_to_proc(self_node);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
