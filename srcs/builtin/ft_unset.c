#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"

static int	unset_args(t_env *env, const char *const *args)
{
	int		status;
	size_t	i;

	status = SUCCESS;
	i = 0;
	while (args[i])
	{
		if (is_valid_key(args[i]))
			env->unset(env, args[i]);
		else
			status = NOT_A_VALID_IDENTIFIER; // print error
		i++;
	}
	return (status);
}

int	ft_unset(const char *const *argv, t_params *params)
{
	const size_t	argc = count_argv(argv);
	int				status;

	if (argc == 1)
		return (SUCCESS);
	if (is_option(argv[1]))
	{
		status = INVALID_OPTION; // print error
		return (status);
	}
	status = unset_args(params->env, &argv[1]);
	return (status);
}
