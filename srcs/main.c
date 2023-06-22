#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

// todo: tmp
static int	free_env_ret_val(t_env *env, int val)
{
	hs_clear(&env->hash);
	ft_free(env);
	return (val);
}

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
			return (free_env_ret_val(params.env, EXIT_FAILURE));
		params.status = execute_command(command, &params);
		deque_clear_all(&command, free);
		if (params.status == PROCESS_ERROR)
			return (free_env_ret_val(params.env, EXIT_FAILURE));
	}
	return (free_env_ret_val(params.env, params.status));
}
