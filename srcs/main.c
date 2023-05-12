#include "minishell.h"
#include "libft.h"

int	minishell(void)
{
	char	*line;
	char	**commands;
	int		process_status;

	process_status = EXIT_SUCCESS;
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
		free_2d_array(&commands);
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
