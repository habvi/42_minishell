#include "minishell.h"
#include "libft.h"

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
	{
		*command = NULL;
		command++;
	}
	return (command);
}

static int	dup_process_and_run(char **exec_command, int *last_exit_status)
{
	extern char	**environ;
	pid_t		pid;

	pid = x_fork();
	if (pid == FORK_ERROR)
		return (FORK_ERROR);
	if (pid == CHILD_PID)
		child_process(exec_command, environ);
	else
	{
		if (parent_process(last_exit_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (EXIT_SUCCESS);
}

int	execute_command(char **exec_command)
{
	int		last_exit_status;
	char	**next_command;

	last_exit_status = EXIT_SUCCESS;
	while (*exec_command)
	{
		next_command = get_next_command(exec_command);
		if (dup_process_and_run(exec_command, &last_exit_status) \
															== PROCESS_ERROR)
			return (PROCESS_ERROR);
		exec_command = next_command;
	}
	return (last_exit_status);
}
