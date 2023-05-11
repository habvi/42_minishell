#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h> // wait
#include "minishell.h"
#include "ft_string.h"

void	*free_all(char **split_strs)
{
	size_t	i;

	i = 0;
	while (split_strs[i] != NULL)
	{
		free(split_strs[i]);
		i++;
	}
	free(split_strs);
	return (NULL);
}

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
	pid_t	pid;
	int		exec_status;

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

int	minishell(void)
{
	char		*line;
	char		**commands;
	int			process_status;

	while (true)
	{
		line = readline("minishell ");
		if (!line)
			break ;
		add_history(line);
		commands = ft_split(line, ' ');
		free(line);
		if (!commands)
			break ;
		// tokenize
		// parse
		process_status = exec(commands);
		free_all(commands);
		if (process_status == PROCESS_ERROR)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(void)
{
	int	process_status;

	process_status = minishell();
	return (process_status);
}
