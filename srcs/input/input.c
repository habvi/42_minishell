#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "ft_string.h"

char	*input_line(void)
{
	char	*line;

	line = readline("minishell ");
	if (!line)
		return (NULL);
	add_history(line);
	return (line);
}
