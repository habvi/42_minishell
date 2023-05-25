#include "minishell.h"
#include "tokenize.h"
#include "deque.h"

static int	minishell(void)
{
	t_deque	*command;
	char	*line;
	int		process_status;

	command = NULL;
	process_status = EXIT_SUCCESS;
	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		command = tokenize(line);
		free(line);
		if (!command)
			return (EXIT_FAILURE);
		// parse()
		process_status = execute_command(command);
		deque_clear_all(&command);
		if (process_status == PROCESS_ERROR)
			return (EXIT_FAILURE);
	}
	return (process_status);
}

int	main(void)
{
	int	process_status;

	process_status = minishell();
	return (process_status);
}
