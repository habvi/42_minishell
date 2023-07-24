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

static char	*set_default_internal_pwd(t_var *var, t_result *result)
{
	char	*pwd_path;
	int		tmp_err;

	pwd_path = get_current_path(&tmp_err);
	ft_free((void **)&pwd_path);
	if (tmp_err)
	{
		if (is_getcwd_failure(tmp_err))
			*result = FAILURE;
		else
			*result = PROCESS_ERROR;
		return (NULL);
	}
	*result = SUCCESS;
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
static t_result	set_context_default_value(t_context *context, \
											bool is_forced_interactive, \
											bool is_rl_event_hook_off)
{
	t_result	result;

	context->var = set_default_environ();
	if (!context->var)
		return (PROCESS_ERROR);
	context->internal_pwd = set_default_internal_pwd(context->var, &result);
	if (result == PROCESS_ERROR)
	{
		context->var->clear(context->var);
		ft_free((void **)&context->var);
		return (PROCESS_ERROR);
	}
	context->is_interactive = set_is_interactive(is_forced_interactive);
	context->status = EXIT_SUCCESS;
	context->is_rl_event_hook_off = is_rl_event_hook_off;
	return (SUCCESS);
}

t_result	init_context(t_context *context, \
							bool is_forced_interactive, \
							bool is_test)
{
	t_result	result;

	set_context_initial_value(context);
	result = set_context_default_value(context, is_forced_interactive, is_test);
	return (result);
}
