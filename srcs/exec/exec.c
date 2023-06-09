#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ms_result.h"
#include "ft_sys.h"

static void	copy_stdio_fd(int *stdin_copy, int *stdout_copy)
{
	// todo: error
	*stdin_copy = dup(STDIN_FILENO);
	*stdout_copy = dup(STDOUT_FILENO);
}

static void	restore_stdio_fd(int stdin_copy, int stdout_copy)
{
	// todo: error
	x_close(STDIN_FILENO);
	x_dup2(stdin_copy, STDIN_FILENO);
	x_close(stdin_copy);

	// todo: error
	x_close(STDOUT_FILENO);
	x_dup2(stdout_copy, STDOUT_FILENO);
	x_close(stdout_copy);
}

static bool	is_node_executable(t_ast *ast_node)
{
	t_node_kind	kind;

	if (!ast_node)
		return (false);
	kind = ast_node->kind;
	return (kind == NODE_KIND_COMMAND || kind == NODE_KIND_SUBSHELL);
}

static t_result	execute_command_internal(t_ast *self_node, t_context *context)
{
	t_result	result;
	int			stdin_copy;
	int			stdout_copy;

	copy_stdio_fd(&stdin_copy, &stdout_copy);
	expand_variables(self_node, context);
	result = redirect_fd(self_node, context);
	if ((result == PROCESS_ERROR) || (result == FAILURE))
		return (result);
	if (is_single_builtin_command(self_node))
		execute_single_builtin(self_node, context); // todo: process error?
	else if (is_node_executable(self_node))
	{
		result = exec_command_each(self_node, context);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	restore_stdio_fd(stdin_copy, stdout_copy);
	return (SUCCESS);
}

t_result	execute_command(t_ast *self_node, t_context *context)
{
	if (!self_node)
		return (SUCCESS);
	if (exec_handle_left_node(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (exec_handle_right_node(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (execute_command_internal(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
