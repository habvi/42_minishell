#include <readline/readline.h>
#include <readline/history.h>
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
