#include <stdlib.h>
#include "minishell.h"

static void	display_splash_screen(void)
{
	ft_dprintf(STDERR_FILENO, \
	"           __         __         __            __  __\n"\
	".--------.|__|.-----.|__|.-----.|  |--..-----.|  ||  |\n"\
	"|        ||  ||     ||  ||__ --||     ||  -__||  ||  |\n"\
	"|__|__|__||__||__|__||__||_____||__|__||_____||__||__|\n");
}

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
	if (!context.is_rl_event_hook_off) // todo: rm submit
		display_splash_screen();
	result = read_eval_print_loop(&context);
	destroy_context(context);
	if (result == PROCESS_ERROR)
		return (EXIT_FAILURE);
	if (context.is_interactive)
		ft_dprintf(STDERR_FILENO, SHELL_EXIT);
	return (context.status);
}
