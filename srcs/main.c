#include <stdlib.h>
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_context	context;
	t_result	result;
	bool		is_forced_interactive;
	bool		is_test;

	if (analyze_option(argc, argv, &is_forced_interactive, &is_test) == FAILURE)
		return (INVALID_OPTION);
	init_context(&context, is_forced_interactive, is_test);
	result = read_eval_print_loop(&context);
	destroy_context(context);
	if (result == PROCESS_ERROR)
		return (EXIT_FAILURE);
	if (context.is_interactive)
		ft_dprintf(STDERR_FILENO, "exit\n");
	return (context.status);
}
