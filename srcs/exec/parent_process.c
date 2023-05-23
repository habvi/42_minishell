#include <sys/wait.h> // wait
#include "minishell.h"

int	parent_process(t_command *cmd, int pipefd[2], int *prev_fd, pid_t pid, int *last_exit_status)
{
	int		status;
	pid_t	wait_pid;

	(void)cmd;
	(void)pipefd;
	(void)prev_fd;
	(void)pid;
	status = 0;
	wait_pid = wait(&status);
	if (wait_pid == WAIT_ERROR)
	{
		perror("wait");
		return (WAIT_ERROR);
	}
	*last_exit_status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}
