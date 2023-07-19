#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ms_result.h"
#include "ft_sys.h"

static bool	is_node_executable(t_ast *ast_node)
{
	const t_node_kind	kind = ast_node->kind;

	return (kind == NODE_KIND_COMMAND || kind == NODE_KIND_SUBSHELL);
}

// execute_single_builtin() not return t_result
static t_result	execute_command_internal(t_ast *self_node, t_context *context)
{
	if (expand_variable_of_cmd_tokens(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (expand_for_heredoc(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (is_single_builtin_command(self_node))
	{
		if (execute_single_builtin(self_node, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	else if (is_node_executable(self_node))
	{
		if (exec_command_each(self_node, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

t_result	execute_command_recursive(t_ast *self_node, t_context *context)
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

t_result	execute_command(t_ast **self_node, \
							t_context *context, \
							t_result heredoc_result)
{
	t_result	exec_result;

	if (heredoc_result == PROCESS_ERROR)
	{
		destroy_ast_node_recursive(self_node);
		return (PROCESS_ERROR);
	}
	exec_result = execute_command_recursive(*self_node, context);
	destroy_ast_tree(self_node, exec_result);
	return (exec_result);
}
