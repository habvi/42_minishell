#include "minishell.h"
#include "ms_builtin.h"

int	ft_export(char *const *argv, t_params *params)
{
	const size_t	argc = count_argv(argv);
	int				status;

	if (argc == 1)
	{
		params->env->print_detail(params->env);
		return (SUCCESS);
	}
	if (is_option(argv[1]))
	{
		status = INVALID_OPTION; // print error
		return (status);
	}
	// malloc: key,value -> error: free

	// key : _ はじく
	// env_set
		// key, value("") =
		// key, NULL

	// env_append
		// key, value("") +=
	return (SUCCESS);
}
