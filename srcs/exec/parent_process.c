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

	errno = 0;
	wait_pid = waitpid(pid, wait_status, NO_OPTION);
	if (wait_pid == WAIT_ERROR)
		return (PROCESS_ERROR);
	if (WIFEXITED(*wait_status))
		*last_status = WEXITSTATUS(*wait_status);
	else if (WIFSIGNALED(*wait_status))
		*last_status = STATUS_SIG_BASE + WTERMSIG(*wait_status);
	else
		*last_status = EXIT_FAILURE; // todo
	return (SUCCESS);
}

static bool	is_child_signaled_sigint(int status)
{
	return (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT);
}

// if wait error, no need for auto perror.
static t_result	wait_all_child_process(bool *signaled_sigint)
{
	int		status;

	*signaled_sigint = false;
	while (true)
	{
		errno = 0;
		if (wait(&status) == WAIT_ERROR)
		{
			if (errno == ECHILD)
				break ;
			perror("wait");
			return (PROCESS_ERROR);
		}
		if (is_child_signaled_sigint(status))
			*signaled_sigint = true;
	}
	return (SUCCESS);
}

static void	put_signal_information(int wait_status, bool signaled_sigint)
{
	const int	last_status = WTERMSIG(wait_status);

	if (last_status == SIGQUIT)
		ft_dprintf(STDERR_FILENO, QUIT);
	if (last_status == SIGINT || signaled_sigint)
		ft_dprintf(STDERR_FILENO, NEWLINE_STR);
}

t_result	parent_process(t_ast *self_node, t_context *context)
{
	int		wait_status;
	bool	signaled_sigint;

	set_signal_for_parent();
	if (handle_parent_pipes(self_node) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (is_last_command_node(self_node))
	{
		if (get_last_command_status(self_node->pid, \
									&wait_status, \
									&context->status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (wait_all_child_process(&signaled_sigint) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		put_signal_information(wait_status, signaled_sigint);
	}
	return (SUCCESS);
}
