#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "ms_builtin.h"

// If an error occurs, will not exit.
static bool	set_is_interactive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
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

void	init_params(t_params *params)
{
	params->env = init_environ();
	params->is_interactive = set_is_interactive();
	params->pwd = get_working_directory(SHELL_INIT);
	// params->pwd == NULL
		// delete PWD in hash
	params->old_pwd = get_old_pwd(params->env);
	params->status = EXIT_SUCCESS;
}
