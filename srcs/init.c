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

static void	init_pwd(char **pwd, t_env *env)
{
	char	*dup_key;
	char	*dup_value;

	*pwd = get_working_directory(SHELL_INIT);
	if (*pwd == NULL)
		env->unset(env, PWD);
	else
	{
		dup_key = ft_strdup(PWD);
		if (!dup_key)
			ft_abort();
		dup_value = ft_strdup(*pwd);
		if (!dup_value)
			ft_abort();
		env->set(env, dup_key, dup_value, ENV_ADD);
	}
}

static char	*get_old_pwd(t_env *env)
{
	(void)env;
	// OLDPWD not in hash
		// set OLDPWD key only
	// OLDPWD
		// search path
			// is invalid directory
				// delete OLDPWD in hash
	return (NULL);
}

static void	init_old_pwd(t_params *params)
{
	params->old_pwd = get_old_pwd(params->env);
}

void	init_params(t_params *params)
{
	params->env = init_environ();
	params->is_interactive = set_is_interactive();
	init_pwd(&params->pwd, params->env);
	init_old_pwd(params);
	params->status = EXIT_SUCCESS;
}
