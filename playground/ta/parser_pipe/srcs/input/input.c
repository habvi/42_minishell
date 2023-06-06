#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "libft.h"

char	*input_line(void)
{
	char	*line;

	rl_outstream = stderr;
	line = readline(PROMPT_NAME);
	if (!line)
		return (NULL);
	add_history(line);
	return (line);
}
