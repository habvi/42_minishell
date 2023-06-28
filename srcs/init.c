#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"

// If an error occurs, will not exit.
static bool	set_is_interactive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

// init_environ set also PWD, OLDPWD.
void	init_params(t_params *params)
{
	params->env = init_environ();
	params->pwd = params->env->get_value(params->env, PWD);
	params->old_pwd = params->env->get_value(params->env, OLDPWD);
	params->is_interactive = set_is_interactive();
	params->status = EXIT_SUCCESS;
}
