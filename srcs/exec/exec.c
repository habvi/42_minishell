#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ft_deque.h"
#include "ft_string.h"
#include "ft_sys.h"

static int	dup_process_and_run(t_command *cmd, \
								t_fd *fd, \
								int *last_exit_status, \
								t_params *params)
{
	extern char	**environ;
	pid_t		pid;

	if (!is_last_command(cmd->next_command))
	{
		if (x_pipe(fd->pipefd) == PIPE_ERROR)
			return (PIPE_ERROR);
	}
	pid = x_fork();
	if (pid == FORK_ERROR)
		return (FORK_ERROR);
	params->is_interactive = false;
	if (pid == CHILD_PID)
		child_process(cmd, fd, environ, params);
	else
	{
		if (parent_process(cmd, fd, pid, last_exit_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (EXIT_SUCCESS);
}

int	execute_command(t_deque *dq_cmd, t_params *params)
{
	t_command		cmd;
	t_fd			fd;
	int				last_exit_status;
	t_deque_node	*exec_cmd;
	size_t			cmd_size;

	init_cmd(&cmd, dq_cmd);
	init_fd(&fd);
	last_exit_status = EXIT_SUCCESS;
	exec_cmd = dq_cmd->node;
	if (is_single_builtin(exec_cmd))
		return (exec_builtin_in_parent_proc(cmd, exec_cmd, params));
	while (exec_cmd)
	{
		cmd.next_command = get_next_command(exec_cmd, &cmd_size);
		cmd.exec_command = convert_command_to_array(exec_cmd, cmd_size);
		if (dup_process_and_run(&cmd, &fd, &last_exit_status, params) \
															== PROCESS_ERROR)
			return (PROCESS_ERROR);
		free_2d_array(&cmd.exec_command);
		exec_cmd = cmd.next_command;
	}
	return (last_exit_status);
}
