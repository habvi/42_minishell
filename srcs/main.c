#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "ft_string.h"

static void	minishell(void)
{
	char		*line;
	char		**commands;
	extern char	**environ;

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
		if (execve(commands[0], commands, environ) == EXECVE_ERROR)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
}

int	main(void)
{
	minishell();
	return (EXIT_SUCCESS);
}
