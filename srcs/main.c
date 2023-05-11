#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "ft_string.h"

static void	minishell(void)
{
	char	*line;
	char	**commands;

	while (true)
	{
		line = readline("minishell ");
		if (!line)
			break ;
		printf("%s\n", line);
		add_history(line);
		commands = ft_split(line, ' ');
		free(line);
		if (!commands)
			break ;
		// tokenize
		// parse
		execve(commands[0], commands, NULL);
	}
}

int	main(void)
{
	minishell();
	return (EXIT_SUCCESS);
}
