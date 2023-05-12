#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "libft.h"

char	*input_line(void)
{
	char	*line;

	line = readline(PROMPT_NAME);
	if (!line)
		return (NULL);
	add_history(line);
	return (line);
}
