#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"

static void	unset_args(const char *const *args, t_env *env, uint8_t *status)
{
	size_t	i;

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

uint8_t	ft_unset(const char *const *argv, t_env *env)
{
	uint8_t	status;
	size_t	i;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	unset_args(&argv[i], env, &status);
	return (status);
}
