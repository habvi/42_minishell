#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ms_result.h"
#include "ft_sys.h"

static void	connect_redirect_fds(t_ast *self_node)
{
	t_redirect	*redirects;

	redirects = (t_redirect *)self_node->redirects;
	if (!redirects)
		return ;
//	ft_dprintf(2, "connect: in:%d, out:%d\n", redirects->in_fd, redirects->out_fd);
	if (redirects->in_fd != IN_FD_INIT)
	{
		if (self_node->prev_fd != IN_FD_INIT)
			x_close(self_node->prev_fd); // todo: error
		self_node->prev_fd = IN_FD_INIT;

		x_close(STDIN_FILENO);
		x_dup2(redirects->in_fd, STDIN_FILENO);
		x_close(redirects->in_fd);
	}
	if (redirects->out_fd != OUT_FD_INIT)
	{
		x_close(STDOUT_FILENO);
		x_dup2(redirects->out_fd, STDOUT_FILENO);
		x_close(redirects->out_fd);
	}
}

static t_result	execute_command_internal(t_ast *self_node, t_context *context)
{
	t_result	result;
	int 		out_copy;

	out_copy = dup(STDOUT_FILENO);
	expand_variables(self_node, context);
	result = redirect_fd(self_node->redirects, context);
	if ((result == PROCESS_ERROR) || (result == FAILURE))
		return (result);

	connect_redirect_fds(self_node);

	if (is_single_builtin_command(self_node))
		execute_single_builtin(self_node, context); // todo: process error?
	else if (exec_command_each(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	x_close(STDOUT_FILENO);
	x_dup2(out_copy, STDOUT_FILENO);
	x_close(out_copy);
	return (SUCCESS);
}

t_result	execute_command(t_ast *self_node, t_context *context)
{
	// int	in_fd_copy;
	// int	out_fd_copy;

	// in_fd_copy = dup(STDIN_FILENO);
	// out_fd_copy = dup(STDOUT_FILENO);

	// ft_dprintf(2, "%s : in[%d],out[%d]\n", __func__, in_fd_copy, out_fd_copy);
	if (!self_node)
		return (SUCCESS);
	if (exec_handle_left_node(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (exec_handle_right_node(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (execute_command_internal(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);

	// x_close(STDIN_FILENO);
	// x_dup2(in_fd_copy, STDIN_FILENO);
	// x_close(in_fd_copy);

	// x_close(STDOUT_FILENO);
	// x_dup2(out_fd_copy, STDOUT_FILENO);
	// x_close(out_fd_copy);

	return (SUCCESS);
}
