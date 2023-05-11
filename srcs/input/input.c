#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "ft_string.h"

char	*input_line()
{
	char	*line;

	line = readline("minishell ");
	if (!line)
		return (NULL);
	add_history(line);
	return (line);
}
