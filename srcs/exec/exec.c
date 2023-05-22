#include <sys/wait.h> // wait
#include "minishell.h"
#include "ft_dprintf.h"
#include "libft.h"

// use PROMPT_NAME
void	child_process(char **commands, char **environ)
{
	debug_func(__func__, __LINE__);
	debug_2d_array(commands);
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

static bool	is_pipe(const char *str)
{
	if (ft_strnlen(str, 2) == 1 && *str == '|')
		return (true);
	return (false);
}

// | command                  -> not handle yet
// command arg                -> return NULL
// command arg |              -> return NULL
// command arg | command2 arg -> return command2
static char	**get_next_command(char **command)
{
	while (*command && !is_pipe(*command))
		command++;
	if (*command)
		command++;
	return (command);
}

int	exec(char **exec_command)
{
	extern char	**environ;
	pid_t		pid;
	int			last_exit_status;
	char		**next_command;

	last_exit_status = EXIT_SUCCESS;
	while (*exec_command)
	{
		next_command = get_next_command(exec_command);
		pid = fork();
		if (pid == FORK_ERROR)
		{
			perror("fork");
			return (FORK_ERROR);
		}
		if (pid == CHILD_PID)
			child_process(exec_command, environ);
		else
		{
			last_exit_status = parent_process();
			if (last_exit_status == PROCESS_ERROR)
				return (last_exit_status);
		}
		exec_command = next_command;
	}
	return (last_exit_status);
}
