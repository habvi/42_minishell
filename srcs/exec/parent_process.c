#include <errno.h>
#include <sys/wait.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_signal.h"
#include "ft_sys.h"

static t_result	get_last_command_status(pid_t pid, \
										int *wait_status, \
										uint8_t *last_status)
{
	pid_t	wait_pid;
	int		sig;

	errno = 0;
	wait_pid = waitpid(pid, wait_status, 0);
	if (wait_pid == WAIT_ERROR)
		return (PROCESS_ERROR);
	if (WIFEXITED(*wait_status))
		*last_status = WEXITSTATUS(*wait_status);
	else if (WIFSIGNALED(*wait_status))
	{
		sig = WTERMSIG(*wait_status);
		if (sig == SIGINT)
			ft_dprintf(STDERR_FILENO, NEWLINE_STR);
		*last_status = STATUS_SIG_BASE + sig;
	}
	else
		*last_status = EXIT_FAILURE; // todo
	return (SUCCESS);
}

static bool	is_child_signaled_sigint(int status)
{
	return (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT);
}

static bool	is_all_child_terminated(int err)
{
	return (err == ECHILD);
}

// if wait error, no need for auto perror.
static t_result	wait_all_child_process(void)
{
	int		status;
	bool	signaled_int_printed;

	signaled_int_printed = false;
	while (true)
	{
		errno = 0;
		if (wait(&status) == WAIT_ERROR)
		{
			if (is_all_child_terminated(errno))
				break ;
			perror("wait");
			return (PROCESS_ERROR);
		}
		if (is_child_signaled_sigint(status) && !signaled_int_printed)
		{
			ft_dprintf(STDERR_FILENO, NEWLINE_STR);
			signaled_int_printed = true;
		}
	}
	return (SUCCESS);
}

t_result	parent_process(t_ast *self_node, t_context *context)
{
	int	wait_status;

	set_signal_for_parent();
	if (handle_parent_pipes(self_node) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (is_last_command_node(self_node))
	{
		if (get_last_command_status(self_node->pid, \
									&wait_status, \
									&context->status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (wait_all_child_process() == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
