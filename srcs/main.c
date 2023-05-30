#include "minishell.h"
#include "tokenize.h"
#include "deque.h"
#include "ft_dprintf.h"
#include "ft_builtin.h"

static int	minishell(void)
{
	t_deque	*command;
	char	*line;
	int		process_status;
	bool	is_exit_shell;

	command = NULL;
	process_status = EXIT_SUCCESS;
	is_exit_shell = false;
	while (!is_exit_shell)
	{
		line = input_line();
		if (!line)
			break ;
		command = tokenize(line);
		free(line);
		if (!command)
			return (EXIT_FAILURE);
		// parse()
		process_status = execute_command(command, &is_exit_shell);
		deque_clear_all(&command);
		if (process_status == PROCESS_ERROR)
			return (EXIT_FAILURE);
	}
	ft_dprintf(STDERR_FILENO, "exit\n");
	return (process_status);
}

int	main(void)
{
	int	process_status;

	process_status = minishell();
	return (process_status);
}
