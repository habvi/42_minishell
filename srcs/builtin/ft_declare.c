#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"

uint8_t	ft_declare(const char *const *argv, t_env *env)
{
	uint8_t	status;
	size_t	i;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	if (!argv[i])
	{
		env->print_detail(env, VAR_ALL);
		return (status);
	}
	return (status);
}
