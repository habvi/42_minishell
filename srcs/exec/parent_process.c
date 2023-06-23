#include <errno.h>
#include <sys/wait.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ft_sys.h"

static int	get_last_command_status(pid_t pid, \
									int *wait_status, \
									uint8_t *last_status)
{
	pid_t	wait_pid;

	wait_pid = x_waitpid(pid, wait_status, 0);
	if (wait_pid != PROCESS_ERROR && WIFEXITED(*wait_status))
		*last_status = WEXITSTATUS(*wait_status);
	else
		return (WAIT_ERROR);
	return (EXIT_SUCCESS);
}

// if wait error, no need for auto perror.
static int	wait_all_child_process(int wait_status)
{
	while (true)
	{
		if (wait(NULL) != WAIT_ERROR)
			continue ;
		if (errno == ECHILD && WIFEXITED(wait_status))
			return (EXIT_SUCCESS);
		else
		{
			perror("wait");
			return (PROCESS_ERROR);
		}
	}
	return (EXIT_SUCCESS);
}

int	parent_process(t_command *cmd, t_fd *fd, pid_t pid, uint8_t *last_status)
{
	int	wait_status;

	if (handle_parent_pipes(cmd, fd) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (is_last_command(cmd->next_command))
	{
		if (get_last_command_status(pid, &wait_status, last_status) \
															== PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (wait_all_child_process(wait_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (EXIT_SUCCESS);
}
