#include <stdlib.h>
#include "minishell.h"
#include "ms_var.h"

static void	set_context_initial_value(t_context *context)
{
	context->var = NULL;
	context->internal_pwd = NULL;
	context->is_interactive = false;
	context->status = EXIT_SUCCESS;
	context->is_return = false;
	context->is_rl_event_hook_on = false;
}

// If an error occurs, will not exit.
static bool	set_is_interactive(bool is_forced_interactive)
{
	if (is_forced_interactive)
		return (true);
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

// set_default_environ set also PWD, OLDPWD.
static void	set_context_default_value(t_context *context, \
										bool is_forced_interactive, \
										bool is_rl_event_hook_on)
{
	t_var	*var;

	context->var = set_default_environ();
	var = context->var;
	context->internal_pwd = var->get_value(var, KEY_PWD);
	context->is_interactive = set_is_interactive(is_forced_interactive);
	context->status = EXIT_SUCCESS;
	context->is_rl_event_hook_on = is_rl_event_hook_on;
}

void	init_context(t_context *context, \
						bool is_forced_interactive, \
						bool is_test)
{
	set_context_initial_value(context);
	set_context_default_value(context, is_forced_interactive, is_test);
}
