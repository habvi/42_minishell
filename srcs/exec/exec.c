#include <sys/wait.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"

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

static t_result	execute_command_recursive(t_ast *self_node, \
											t_context *context)
{
	if (!self_node)
		return (SUCCESS);

	// ( )
	// fork -> execute_command(exec)

	// node left
	if (self_node->left)
	{
		if (execute_command_recursive(self_node->left, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		//  [command] after left: prev_fd = left->pipe_fd[READ]
		if (self_node->kind == NODE_KIND_OP_PIPE && self_node->right)
			self_node->right->prev_fd = self_node->prev_fd;
	}

	// &&, ||
	if (!is_executable_right_node(self_node, context->status))
		return (CONTINUE);

	// node right
	if (self_node->right)
	{
		if (execute_command_recursive(self_node->right, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		// [command] after right: prev_fd = left->pipe_fd[READ]
		if (self_node->kind == NODE_KIND_OP_PIPE && self_node->parent)
			self_node->parent->prev_fd = self_node->prev_fd;
	}

	// command
	if (is_single_builtin_command(self_node))
		execute_single_builtin(self_node, context); // todo: process error?
	else if (exec_command_each(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

t_result	execute_command(t_ast *ast, t_context *context)
{
	t_result	result;

	result = execute_command_recursive(ast, context);
	return (result);
}
