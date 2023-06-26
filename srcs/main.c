#include <stdlib.h>
#include "minishell.h"

int	main(void)
{
	t_params	params;
	t_result	result;

	init_params(&params);
	result = read_eval_print_loop(&params);
	destroy(params);
	if (result == PROCESS_ERROR)
		return (EXIT_FAILURE);
	return (params.status);
}
