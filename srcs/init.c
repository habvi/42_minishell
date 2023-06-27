#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "ms_builtin.h"

// If an error occurs, will not exit.
static bool	set_is_interactive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

void	init_params(t_params *params)
{
	params->env = init_environ();
	params->is_interactive = set_is_interactive();
	params->pwd = get_working_directory(SHELL_INIT);
	params->status = EXIT_SUCCESS;
}
