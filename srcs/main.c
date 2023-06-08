#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_sys.h"

// If an error occurs, will not exit.
static bool	set_is_interactive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

static int	minishell(void)
{
	t_deque	*command;
	char	*line;
	int		process_status;
	bool	is_interactive;

	ft_dprintf(2, "[isatty(): %d, %d]\n", isatty(STDIN_FILENO), isatty(STDOUT_FILENO));
	command = NULL;
	process_status = EXIT_SUCCESS;
	is_interactive = set_is_interactive();
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
		process_status = execute_command(command, is_interactive);
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
