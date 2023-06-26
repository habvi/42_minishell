#include "minishell.h"
#include "ms_exec.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"

static void	exec_builtin_in_parent_proc(t_command cmd, \
										t_deque_node *exec_cmd, \
										t_params *params)
{
	size_t	cmd_size;

	cmd.next_command = get_next_command(exec_cmd, &cmd_size);
	cmd.exec_command = convert_command_to_array(exec_cmd, cmd_size);
	params->status = call_builtin_command(\
		(const char *const *)cmd.exec_command, params);
	free_2d_array(&cmd.exec_command);
}

static t_result	dup_process_and_run(t_command *cmd, \
								t_fd *fd, \
								uint8_t *last_status, \
								t_params *params)
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
	params->is_interactive = false;
	if (pid == CHILD_PID)
		child_process(cmd, fd, environ, params);
	else
	{
		if (parent_process(cmd, fd, pid, last_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

t_result	exec_command_iter(t_deque_node *exec_cmd, \
								t_command cmd, \
								t_params *params)
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
		if (dup_process_and_run(&cmd, &fd, &last_status, params) \
															== PROCESS_ERROR)
			return (PROCESS_ERROR);
		free_2d_array(&cmd.exec_command);
		exec_cmd = cmd.next_command;
	}
	params->status = last_status;
	return (SUCCESS);
}

t_result	execute_command(t_deque *dq_cmd, t_params *params)
{
	t_command		cmd;
	t_deque_node	*exec_cmd;

	init_cmd(&cmd, dq_cmd);
	exec_cmd = dq_cmd->node;
	if (is_single_builtin(exec_cmd))
	{
		exec_builtin_in_parent_proc(cmd, exec_cmd, params);
		return (SUCCESS);
	}
	if (exec_command_iter(exec_cmd, cmd, params) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
