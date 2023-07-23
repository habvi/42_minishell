#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static bool	is_empty_line(const char *line)
{
	return (line[0] == CHR_NULL);
}

static bool	is_ignorespace(const char *line)
{
	return (line[0] == SPACE);
}

static void	add_accept_line_to_history(const char *line)
{
	if (is_empty_line(line))
		return ;
	if (is_ignorespace(line))
		return ;
	add_history(line);
}

char	*input_line(void)
{
	char	*line;

	rl_outstream = stderr;
	line = readline(PROMPT_NAME);
	if (!line)
		return (NULL);
	add_accept_line_to_history(line);
	return (line);
}
