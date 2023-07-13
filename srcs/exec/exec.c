#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ms_result.h"
#include "ft_sys.h"

static void	connect_redirect_fds(t_ast *self_node)
{
	if (self_node->proc_fd[IN] != IN_FD_INIT)
	{
		if (self_node->prev_fd != IN_FD_INIT)
			x_close(self_node->prev_fd); // todo: error
		self_node->prev_fd = IN_FD_INIT;

		x_close(STDIN_FILENO);
		x_dup2(self_node->proc_fd[IN], STDIN_FILENO);
		x_close(self_node->proc_fd[IN]);
	}
	if (self_node->proc_fd[OUT] != OUT_FD_INIT)
	{
		x_close(STDOUT_FILENO);
		x_dup2(self_node->proc_fd[OUT], STDOUT_FILENO);
		x_close(self_node->proc_fd[OUT]);
	}
}

static t_result	execute_command_internal(t_ast *self_node, t_context *context)
{
	t_result	result;

	expand_variables(self_node, context);
	result = redirect_fd(self_node, context);
	if ((result == PROCESS_ERROR) || (result == FAILURE))
		return (result);

	connect_redirect_fds(self_node);

	if (is_single_builtin_command(self_node))
		execute_single_builtin(self_node, context); // todo: process error?
	else if (exec_command_each(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

t_result	execute_command(t_ast *self_node, t_context *context)
{
	int	in_copy;
	int out_copy;

	in_copy = dup(STDIN_FILENO);
	out_copy = dup(STDOUT_FILENO);

	if (!self_node)
		return (SUCCESS);
	if (exec_handle_left_node(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (exec_handle_right_node(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (execute_command_internal(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);

	x_close(STDIN_FILENO);
	x_dup2(in_copy, STDIN_FILENO);
	x_close(in_copy);

	x_close(STDOUT_FILENO);
	x_dup2(out_copy, STDOUT_FILENO);
	x_close(out_copy);
	return (SUCCESS);
}
