#include <stdlib.h>
#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"

static void	set_context_initial_value(t_context *context)
{
	context->var = NULL;
	context->internal_pwd = NULL;
	context->is_interactive = false;
	context->status = EXIT_SUCCESS;
	context->is_return = false;
	context->is_rl_event_hook_off = false;
}

static char	*set_default_internal_pwd(t_var *var)
{
	char	*pwd_path;
	int		tmp_err;

	pwd_path = get_current_path(&tmp_err);
	ft_free(&pwd_path);
	if (tmp_err)
		return (NULL);
	return (var->get_value(var, KEY_PWD));
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
										bool is_rl_event_hook_off)
{
	context->var = set_default_environ();
	context->internal_pwd = set_default_internal_pwd(context->var);
	context->is_interactive = set_is_interactive(is_forced_interactive);
	context->status = EXIT_SUCCESS;
	context->is_rl_event_hook_off = is_rl_event_hook_off;
}

void	init_context(t_context *context, \
						bool is_forced_interactive, \
						bool is_rl_hook_off)
{
	set_context_initial_value(context);
	set_context_default_value(context, is_forced_interactive, is_rl_hook_off);
}
