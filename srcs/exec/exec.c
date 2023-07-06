#include "minishell.h"
#include "ms_exec.h"
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

t_result	execute_command(t_deque *dq_cmd, t_context *context)
{
	t_command		cmd;
	t_deque_node	*exec_cmd;

	if (!dq_cmd) // todo: for parse test. erase.
		return (SUCCESS); // todo: for parse test. erase.
	init_cmd(&cmd, dq_cmd);
	exec_cmd = dq_cmd->node;
	if (is_single_builtin(exec_cmd))
	{
		exec_builtin_in_parent_proc(cmd, exec_cmd, context);
		return (SUCCESS);
	}
	if (exec_command_iter(exec_cmd, cmd, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
