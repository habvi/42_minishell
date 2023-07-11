#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ms_result.h"

static t_result	execute_command_internal(t_ast *self_node, t_context *context)
{
	t_result	result;

	expand_variables(self_node, context);
	result = redirect_fd(self_node->redirects, context);
	if ((result == PROCESS_ERROR) || (result == FAILURE))
		return (result);
	if (is_single_builtin_command(self_node))
		execute_single_builtin(self_node, context); // todo: process error?
	else if (exec_command_each(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
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
