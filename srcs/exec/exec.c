#include <sys/wait.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"

// &&, ||
static bool	is_executable_right_node(t_ast *self_node, uint8_t status)
{
	if (!is_node_kind_and_or(self_node->kind))
		return (true);
	if (self_node->kind == NODE_KIND_OP_AND && status == 0)
		return (true);
	if (self_node->kind == NODE_KIND_OP_OR && status != 0)
		return (true);
	return (false);
}

static t_result	execute_command_internal(t_ast *self_node, t_context *context)
{
	if (is_single_builtin_command(self_node))
		execute_single_builtin(self_node, context); // todo: process error?
	else if (exec_command_each(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

// todo: redirect, expansion
t_result	execute_command(t_ast *self_node, t_context *context)
{
	if (!self_node)
		return (SUCCESS);
	if (exec_handle_left_node(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (!is_executable_right_node(self_node, context->status))
		return (CONTINUE);
	if (exec_handle_right_node(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (execute_command_internal(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
