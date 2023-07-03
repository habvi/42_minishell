#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

static void	destroy_command(t_deque *command)
{
	deque_clear_all(&command, free);
}

t_result	read_eval_print_loop(t_context *context)
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
		debug_token_dq(command, "repl");
		deque_clear_all(&command, del_token);
		continue ;
		result = execute_command(command, context);
		destroy_command(command);
		if (result == PROCESS_ERROR)
			break ;
	}
	return (result);
}
