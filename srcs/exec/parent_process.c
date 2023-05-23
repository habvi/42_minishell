#include <sys/wait.h> // wait
#include <errno.h>
#include "minishell.h"
#include "ft_dprintf.h"

int	parent_process(t_command *cmd, t_fd *fd, pid_t pid, int *last_exit_status)
{
	int		status;
	pid_t	wait_pid;

	(void)cmd;
	if (!is_first_command(fd->prev_fd))
	{
		// SYS_ERROR
		close(fd->prev_fd);
	}
	if (!is_last_command(*cmd->next_command))
	{
		fd->prev_fd = fd->pipefd[READ];
		// SYS_ERROR
		close(fd->pipefd[WRITE]);
		return (EXIT_SUCCESS);
	}
	wait_pid = waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*last_exit_status = WEXITSTATUS(status);
	else
	{
		perror("waitpid");
		return (PROCESS_ERROR);
	}
	while (true)
	{
		wait_pid = wait(NULL);
		if (wait_pid == WAIT_ERROR)
		{
			if (errno == ECHILD && WIFEXITED(status))
			{
				ft_dprintf(STDERR_FILENO, "\nchild exit success! status: %d, last cmd exit status: %d\n", WIFEXITED(status), *last_exit_status);
				return (EXIT_SUCCESS);
			}
			else
			{
				perror("wait");
				return (PROCESS_ERROR);
			}
		}
	}
	return (EXIT_SUCCESS);
}
