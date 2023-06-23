#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

int	main(void)
{
	t_params	params;
	t_deque		*command;
	char		*line;
	uint8_t		*status;

	init_params(&params);
	status = &params.status;
	command = NULL;
	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		command = tokenize(line);
		ft_free(line);
		if (execute_command(command, status, &params) == PROCESS_ERROR)
			return (EXIT_FAILURE);
		deque_clear_all(&command, free);
	}
	hs_clear(&params.env->hash);
	ft_free(params.env);
	return (*status);
}
