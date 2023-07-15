#include <stdlib.h>
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_context	context;
	t_result	result;
	bool		is_forced_interactive;

	if (analyze_option(argc, argv, &is_forced_interactive) == FAILURE)
		return (INVALID_OPTION);
	init_context(&context, is_forced_interactive);
	result = read_eval_print_loop(&context);
	destroy_context(context);
	if (result == PROCESS_ERROR)
		return (EXIT_FAILURE);
	return (context.status);
}
