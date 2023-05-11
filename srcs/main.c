#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	minishell(void)
{
	char	*line;

	while (true)
	{
		line = readline("minishell ");
		if (!line)
			break ;
		printf("%s\n", line);
		add_history(line);
		free(line);
		// tokenize
		// parse
		// exec
	}
}

int	main(void)
{
	minishell();
	return (EXIT_SUCCESS);
}
