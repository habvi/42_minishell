#include "minishell.h"
#include "ft_string.h"

int	minishell(void)
{
	char	*line;
	char	**commands;
	int		process_status;

	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		// tokenize
		commands = ft_split(line, ' ');
		free(line);
		if (!commands)
			return (EXIT_FAILURE);
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
