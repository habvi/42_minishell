#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"

static bool	is_matching_condition_of_traverse_left_node(const t_ast *self_node)
{
	return (self_node->kind != NODE_KIND_SUBSHELL && self_node->left);
}

t_result	exec_handle_left_node(t_ast *self_node, t_context *context)
{
	if (!is_matching_condition_of_traverse_left_node(self_node))
		return (SUCCESS);
	if (execute_command_recursive(self_node->left, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (self_node->kind == NODE_KIND_OP_PIPE && self_node->right)
		self_node->right->prev_fd = self_node->prev_fd;
	return (SUCCESS);
}

// &&, ||
static bool	is_executable_right_node(const t_ast *self_node, \
										const t_context *context)
{
	if (context->is_return)
		return (false);
	if (!is_node_kind_and_or(self_node->kind))
		return (true);
	if (self_node->kind == NODE_KIND_OP_AND && context->status == EXIT_SUCCESS)
		return (true);
	if (self_node->kind == NODE_KIND_OP_OR && context->status != EXIT_SUCCESS)
		return (true);
	return (false);
}

static bool	is_matching_condition_of_traverse_right_node(\
							const t_ast *self_node, const t_context *context)
{
	if (!is_executable_right_node(self_node, context))
		return (false);
	if (self_node->kind != NODE_KIND_SUBSHELL && self_node->right)
		return (true);
	return (false);
}

t_result	exec_handle_right_node(t_ast *self_node, t_context *context)
{
	if (!is_matching_condition_of_traverse_right_node(self_node, context))
		return (SUCCESS);
	if (execute_command_recursive(self_node->right, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (self_node->kind == NODE_KIND_OP_PIPE && self_node->parent)
		self_node->parent->prev_fd = self_node->prev_fd;
	return (SUCCESS);
}
