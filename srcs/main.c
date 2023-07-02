#include <stdlib.h>
#include "minishell.h"

int	main(void)
{
	t_context	context;
	t_result	result;

	init_context(&context);
	result = read_eval_print_loop(&context);
	destroy_context(context);
	if (result == PROCESS_ERROR)
		return (EXIT_FAILURE);
	return (context.status);
}
