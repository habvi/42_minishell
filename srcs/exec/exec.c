#include <sys/wait.h> // wait
#include "minishell.h"
#include "ft_string.h"
#include "ft_put.h"		// ft_putendl_fd -> ft_dprintf

void	child_process(char **commands, char **environ)
{
	if (execve(commands[0], commands, environ) == EXECVE_ERROR)
	{
		ft_putstr_fd( "minishell: ", STDERR_FILENO);
		ft_putstr_fd( commands[0], STDERR_FILENO);
		ft_putstr_fd( ": No such file or directory\n", STDERR_FILENO);
		free_all(commands);
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
