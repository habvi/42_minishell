#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "ms_var.h"
#include "ft_string.h"

static void	set_context_initial_value(t_context *context)
{
	context->var = NULL;
	context->internal_pwd = NULL;
	context->is_interactive = false;
	context->status = EXIT_SUCCESS;
}

// If an error occurs, will not exit.
static bool	set_is_interactive(void)
{
	return (true);
	// return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

// set_default_environ set also PWD, OLDPWD.
static void	set_context_default_value(t_context *context)
{
	t_var	*var;

	context->var = set_default_environ();
	var = context->var;
	context->internal_pwd = var->get_value(var, KEY_PWD);
	context->is_interactive = set_is_interactive();
	context->status = EXIT_SUCCESS;
}

void	init_context(t_context *context)
{
	set_context_initial_value(context);
	set_context_default_value(context);
}
