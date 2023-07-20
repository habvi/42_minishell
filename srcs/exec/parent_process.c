#include <sys/wait.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_sys.h"

t_result	get_last_command_status(pid_t pid, \
									int *wait_status, \
									uint8_t *last_status)
{
	pid_t	wait_pid;

	wait_pid = x_waitpid(pid, wait_status, NO_OPTION);
	if (wait_pid != WAIT_ERROR && WIFEXITED(*wait_status))
		*last_status = WEXITSTATUS(*wait_status);
	else
		return (PROCESS_ERROR);
	return (SUCCESS);
}

// if wait error, no need for auto perror.
t_result	wait_all_child_process(int wait_status)
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

t_result	parent_process(t_ast *self_node, t_context *context)
{
	int	wait_status;

	if (handle_parent_pipes(self_node) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (is_last_command_node(self_node))
	{
		if (get_last_command_status(self_node->pid, \
									&wait_status, \
									&context->status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (wait_all_child_process(wait_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
