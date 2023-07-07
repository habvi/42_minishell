#include <errno.h>
#include <sys/wait.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ft_sys.h"
/*
static t_result	get_last_command_status(pid_t pid, \
									int *wait_status, \
									uint8_t *last_status)
{
	pid_t	wait_pid;

	wait_pid = x_waitpid(pid, wait_status, 0);
	if (wait_pid != WAIT_ERROR && WIFEXITED(*wait_status))
		*last_status = WEXITSTATUS(*wait_status);
	else
		return (PROCESS_ERROR);
	return (SUCCESS);
}

// if wait error, no need for auto perror.
static t_result	wait_all_child_process(int wait_status)
{
	while (true)
	{
		errno = 0;
		if (wait(NULL) != WAIT_ERROR)
			continue ;
		if (errno == ECHILD && WIFEXITED(wait_status))
			break ;
		else
		{
			perror("wait");
			return (PROCESS_ERROR);
		}
	}
	return (SUCCESS);
}

//todo fd->fds?
t_result	parent_process(t_command *cmd, \
							t_fd *fd, \
							pid_t pid, \
							uint8_t *last_status)
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
	return (SUCCESS);
}
*/

//static t_result	handle_parent_pipes_except_first(t_fd *fd)
//{
//	if (x_close(fd->prev_fd) == CLOSE_ERROR)
//		return (PROCESS_ERROR);
//	return (SUCCESS);
//}

t_result	parent_process(t_ast *self_node)
{
	if (handle_parent_pipes(self_node) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
