#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"

static void	set_context_initial_value(t_context *context)
{
	context->env = NULL;
	context->internal_pwd = NULL;
	context->internal_old_pwd = NULL;
	context->is_interactive = false;
	context->status = EXIT_SUCCESS;
}

// If an error occurs, will not exit.
static bool	set_is_interactive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

static void	set_context_default_value(t_context *context)
{
	t_env	*env;

	context->env = init_environ(context);
	env = context->env;
	context->internal_pwd = env->get_value(env, KEY_PWD);
	context->internal_old_pwd = env->get_value(env, KEY_OLDPWD);
	context->is_interactive = set_is_interactive();
	context->status = EXIT_SUCCESS;
}

// init_environ set also PWD, OLDPWD.
void	init_context(t_context *context)
{
	set_context_initial_value(context);
	set_context_default_value(context);
}
