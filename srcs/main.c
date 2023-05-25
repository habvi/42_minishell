#include "minishell.h"
#include "tokenize.h"
#include "deque.h"

static int	minishell(void)
{
	t_deque	*command;
	char	*line;
	int		process_status;

	command = NULL;
	process_status = EXIT_SUCCESS;
	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		command = tokenize(line);
		free(line);
		debug_deque_print(command, __func__);
		deque_clear_all(&command);
		// ----------------------------------
		// if (!cmd.head)
		// 	return (EXIT_FAILURE);
		// cmd.exec_command = cmd.head;
		// // parse
		// process_status = execute_command(&cmd);
		// free_2d_array(&cmd.head);
		// if (process_status == PROCESS_ERROR)
		// 	return (EXIT_FAILURE);
	}
	return (process_status);
}

int	main(void)
{
	int	process_status;

	process_status = minishell();
	return (process_status);
}
