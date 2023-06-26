#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

t_result	read_eval_print_loop(t_params *params)
{
	t_deque		*command;
	t_result	result;
	char		*line;

	command = NULL;
	result = SUCCESS;
	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		command = tokenize(line);
		ft_free(&line);
		result = execute_command(command, params);
		deque_clear_all(&command, free);
		if (result == PROCESS_ERROR)
			break ;
	}
	return (result);
}
