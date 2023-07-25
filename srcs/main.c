#include <stdlib.h>
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_context	context;
	t_result	result;
	bool		is_forced_interactive;
	bool		is_rl_hook_off;

	result = analyze_op(argc, argv, &is_forced_interactive, &is_rl_hook_off);
	if (result == FAILURE)
		return (INVALID_OPTION);
	result = init_context(&context, is_forced_interactive, is_rl_hook_off);
	if (result == PROCESS_ERROR)
		return (EXIT_FAILURE);
	result = read_eval_print_loop(&context);
	destroy_context(context);
	if (result == PROCESS_ERROR)
		return (EXIT_FAILURE);
	if (context.is_interactive)
		ft_dprintf(STDERR_FILENO, SHELL_EXIT);
	return (context.status);
}
