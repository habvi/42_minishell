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

static t_result	execute_subshell(t_ast *root_node, t_context *context)
{

	if (x_pipe(root_node->pipe_fd) == PIPE_ERROR)
		return (PROCESS_ERROR);
	root_node->pid = x_fork();
	if (root_node->pid == FORK_ERROR)
		return (PROCESS_ERROR);
	context->is_interactive = false;
	root_node->left->pipe_fd[READ] = root_node->pipe_fd[READ];
	root_node->left->pipe_fd[WRITE] = root_node->pipe_fd[WRITE];
	root_node->left->prev_fd = root_node->prev_fd;
	if (root_node->pid == CHILD_PID)
	{
		// if (handle_child_pipes(root_node) == PROCESS_ERROR)
		// 	exit(EXIT_FAILURE);
		if (execute_command(root_node->left, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		exit (context->status);
	}
	else
	{
		int	wait_status;

		// usleep(50000);
		root_node->prev_fd = root_node->left->pipe_fd[READ];
		// if (handle_parent_pipes(root_node) == PROCESS_ERROR)
		// 	return (PROCESS_ERROR);
		if (get_last_command_status(\
				root_node->pid, &wait_status, &context->status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (wait_all_child_process(wait_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	// char c;
	// while (read(root_node->prev_fd, &c, 1) > 0)
	// {
	// 	write(2, &c, 1);
	// }
	if (root_node->parent)
		root_node->parent->prev_fd = root_node->prev_fd;
	return (SUCCESS);
}

static t_result	execute_command_recursive(t_ast *self_node, t_context *context)
{
	if (!self_node)
		return (SUCCESS);

	// debug_print_ast_tree(self_node, "subshell");
	// ( )
	if (is_node_kind_subshell(self_node->kind))
		return (execute_subshell(self_node, context));

	// node left
	if (self_node->left)
	{
		if (execute_command_recursive(self_node->left, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		// subshell
		if (self_node->kind == NODE_KIND_SUBSHELL)
			self_node->parent->prev_fd = self_node->prev_fd;
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
	// debug_print_ast_tree(ast, "aaaa");
	return (result);
}
