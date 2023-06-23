#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"

static void	unset_args(const char *const *args, t_env *env, uint8_t *status)
{
	size_t	i;

	*status = SUCCESS;
	i = 0;
	while (args[i])
	{
		if (is_valid_key(args[i]))
			env->unset(env, args[i]);
		else
			*status = NOT_A_VALID_IDENTIFIER; // print error
		i++;
	}
}

uint8_t	ft_unset(const char *const *argv, t_params *params)
{
	const size_t	argc = count_argv(argv);
	uint8_t			status;

	if (argc == 1)
		return (SUCCESS);
	if (is_option(argv[1]))
	{
		status = INVALID_OPTION; // print error
		return (status);
	}
	unset_args(&argv[1], params->env, &status);
	return (status);
}
