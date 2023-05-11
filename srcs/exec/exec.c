#include <sys/wait.h> // wait
#include "minishell.h"

void	child_process(char **commands, char **environ)
{
	if (execve(commands[0], commands, environ) == EXECVE_ERROR)
	{
		perror("execve");
		free_all(commands);
		exit(EXIT_FAILURE);
	}
}

int	parent_process(void)
{
	int		status;
	pid_t	wait_pid;

	status = 0;
	wait_pid = wait(&status);
	if (wait_pid == WAIT_ERROR)
	{
		perror("wait");
		return (WAIT_ERROR);
	}
	return (status);
}

int	exec(char **commands)
{
	extern char	**environ;
	pid_t		pid;
	int			exec_status;

	pid = fork();
	if (pid == FORK_ERROR)
	{
		perror("fork");
		return (FORK_ERROR);
	}
	if (pid == CHILD_PID)
		child_process(commands, environ);
	exec_status = parent_process();
	return (exec_status);
}
