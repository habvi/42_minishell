#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"

// {"env", "arg1", "arg2", ..., NULL};
uint8_t	ft_env(const char *const *argv, t_var *var)
{
	uint8_t			status;
	const size_t	argc = count_argv(argv);

	status = EXIT_SUCCESS;
	if (argc != 1)
	{
		// todo : error handring
		status = INVALID_OPTION; // print error
		return (status);
	}
	var->env_print(var);
	return (status);
}
