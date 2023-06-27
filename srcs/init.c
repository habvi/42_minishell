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

void	init_params(t_params *params)
{
	params->env = init_environ();
	params->is_interactive = set_is_interactive();
	init_pwd(&params->pwd, params->env);
	init_old_pwd(params);
	params->status = EXIT_SUCCESS;
}
