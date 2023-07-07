#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"

static void	exec_builtin_in_parent_proc(t_command cmd, \
										t_deque_node *exec_cmd, \
										t_context *context)
{
	size_t	cmd_size;

	cmd.next_command = get_next_command(exec_cmd, &cmd_size);
	cmd.exec_command = convert_command_to_array(exec_cmd, cmd_size);
	context->status = call_builtin_command(\
		(const char *const *)cmd.exec_command, context);
	free_2d_array(&cmd.exec_command);
}

static t_result	dup_process_and_run(t_command *cmd, \
								t_fd *fd, \
								uint8_t *last_status, \
								t_context *context)
{
	extern char	**environ;
	pid_t		pid;

	if (!is_last_command(cmd->next_command))
	{
		if (x_pipe(fd->pipefd) == PIPE_ERROR)
			return (PROCESS_ERROR);
	}
	pid = x_fork();
	if (pid == FORK_ERROR)
		return (PROCESS_ERROR);
	context->is_interactive = false;
	if (pid == CHILD_PID)
		child_process(cmd, fd, environ, context);
	else
	{
		if (parent_process(cmd, fd, pid, last_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

t_result	exec_command_iter(t_deque_node *exec_cmd, \
								t_command cmd, \
								t_context *context)
{
	uint8_t	last_status;
	size_t	cmd_size;
	t_fd	fd;

	init_fd(&fd);
	last_status = EXIT_SUCCESS;
	while (exec_cmd)
	{
		cmd.next_command = get_next_command(exec_cmd, &cmd_size);
		cmd.exec_command = convert_command_to_array(exec_cmd, cmd_size);
		if (dup_process_and_run(&cmd, &fd, &last_status, context) \
															== PROCESS_ERROR)
			return (PROCESS_ERROR);
		free_2d_array(&cmd.exec_command);
		exec_cmd = cmd.next_command;
	}
	context->status = last_status;
	return (SUCCESS);
}

///////////////////////////////////////////////////////////////////////////////

// &&, ||, subshell, command, (ex |)
static bool	is_single_builtin_command(t_ast *self_node, t_ast *parent_node)
{
	return (self_node->kind == NODE_KIND_COMMAND \
			&& parent_node->kind != NODE_KIND_OP_PIPE);
}

static t_result	execute_command_recursive(t_ast *self_node, \
											t_ast *parent_node, \
											t_context *context)
{
	if (!self_node)
		return (SUCCESS);
	if (self_node->left)
	{
		if (execute_command_recursive(self_node->left, self_node, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (self_node->right)
	{
		if (execute_command_recursive(self_node->right, self_node, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (is_single_builtin_command(self_node, parent_node))
	{
		if (execute_single_builtin(self_node, context) == PROCESS_ERROR)
				return (PROCESS_ERROR);
	}
	// else if (exec_command(ast) == PROCESS_ERROR)
	// 	return (PROCESS_ERROR);
	return (SUCCESS);
}

t_result	execute_command(t_ast *ast, t_context *context)
{
	t_result	result;

	result = execute_command_recursive(ast, NULL, context);
	return (result);
}
