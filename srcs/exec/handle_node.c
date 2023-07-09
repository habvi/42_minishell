#include <sys/wait.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"

static bool	is_matching_condition_of_traverse_left_node(t_ast *self_node)
{
	return (self_node->kind != NODE_KIND_SUBSHELL && self_node->left);
}

t_result	exec_handle_left_node(t_ast *self_node, t_context *context)
{
	if (!is_matching_condition_of_traverse_left_node(self_node))
		return (SUCCESS);
	if (execute_command(self_node->left, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (self_node->kind == NODE_KIND_OP_PIPE && self_node->right)
		self_node->right->prev_fd = self_node->prev_fd;
	return (SUCCESS);
}

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

static bool	is_matching_condition_of_traverse_right_node(t_ast *self_node, \
															uint8_t status)
{
	if (!is_executable_right_node(self_node, status))
		return (false);
	if (self_node->kind != NODE_KIND_SUBSHELL && self_node->right)
		return (true);
	return (false);
}

t_result	exec_handle_right_node(t_ast *self_node, t_context *context)
{
	if (!is_matching_condition_of_traverse_right_node(self_node, \
														context->status))
		return (SUCCESS);
	if (execute_command(self_node->right, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (self_node->kind == NODE_KIND_OP_PIPE && self_node->parent)
		self_node->parent->prev_fd = self_node->prev_fd;
	return (SUCCESS);
}
