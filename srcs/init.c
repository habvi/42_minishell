#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

// If an error occurs, will not exit.
static bool	set_is_interactive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

void	init_params(t_params *params)
{
	t_env	*env;

	env = init_environ();
	// todo: error
	params->env = env;
	params->is_interactive = set_is_interactive();
	params->pwd = NULL;
	params->status = EXIT_SUCCESS;
}
