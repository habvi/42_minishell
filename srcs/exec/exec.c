#include <sys/wait.h> // wait
#include "minishell.h"
#include "ft_dprintf.h"
#include "libft.h"

// use PROMPT_NAME
void	child_process(char **commands, char **environ)
{
	printf("chi : %p\n", commands);
	// if (!commands[0])
	// 	exit(EXIT_SUCCESS);
	if (execve(commands[0], commands, environ) == EXECVE_ERROR)
	{
		// write or malloc error
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", \
											commands[0], EXIT_MSG_NO_SUCH_FILE);
		free_2d_array(&commands);
		exit(EXIT_CODE_NO_SUCH_FILE);
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
	return (WEXITSTATUS(status));
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
