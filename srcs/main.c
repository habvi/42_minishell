#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

int	main(void)
{
	t_params	params;
	t_deque		*command;
	char		*line;

	init_params(&params);
	command = NULL;
	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		command = tokenize(line);
		free(line);
		if (!command)
			return (EXIT_FAILURE);
		// parse()
		params.status = execute_command(command, &params);
		deque_clear_all(&command, free);
		if (params.status == PROCESS_ERROR)
			return (EXIT_FAILURE);
	}
	return (params.status);
}
