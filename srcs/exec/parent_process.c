#include <sys/wait.h> // wait
#include <errno.h> // ECHILD
#include "minishell.h"
#include "ft_dprintf.h"
#include "libft.h"

static int	get_last_command_status(\
								pid_t pid, int *status, int *last_exit_status)
{
	pid_t	wait_pid;

	wait_pid = x_waitpid(pid, status, 0);
	if (wait_pid != PROCESS_ERROR && WIFEXITED(*status))
		*last_exit_status = WEXITSTATUS(*status);
	else
		return (WAIT_ERROR);
	return (EXIT_SUCCESS);
}

// if wait error, no need for auto perror.
static int	wait_all_child_process(int status)
{
	while (true)
	{
		if (wait(NULL) != WAIT_ERROR)
			continue ;
		if (errno == ECHILD && WIFEXITED(status))
			return (EXIT_SUCCESS);
		else
		{
			perror("wait");
			return (PROCESS_ERROR);
		}
	}
	return (EXIT_SUCCESS);
}

int	parent_process(t_command *cmd, t_fd *fd, pid_t pid, int *last_exit_status)
{
	int	status;

	if (handle_parent_pipes(cmd, fd) == PROCESS_ERROR)
		exit(EXIT_FAILURE);
	if (get_last_command_status(pid, &status, last_exit_status) \
															== PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (wait_all_child_process(status) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	// ft_dprintf(STDERR_FILENO, "\nchild exit success! ");
	// ft_dprintf(STDERR_FILENO, "status: %d,", WIFEXITED(status));
	// ft_dprintf(STDERR_FILENO, "exit status: %d\n", *last_exit_status);
	return (EXIT_SUCCESS);
}
