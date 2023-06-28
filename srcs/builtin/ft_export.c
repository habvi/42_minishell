#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"

static void	declare_all(const char *const *args, t_env *env, uint8_t *status)
{
	size_t		i;
	t_result	result;

	i = 0;
	while (args[i])
	{
		result = env_declare_arg(args[i], env);
		if (result == FAILURE)
		{
			*status = NOT_A_VALID_IDENTIFIER;
			// todo: func
			ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n", \
				SHELL_NAME, CMD_EXPORT, args[i], ERROR_MSG_NOT_VALID_ID);
		}
		i++;
	}
}

uint8_t	ft_export(const char *const *argv, t_params *params)
{
	uint8_t	status;
	size_t	i;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	if (!argv[i])
	{
		params->env->print_detail(params->env);
		return (status);
	}
	declare_all(&argv[i], params->env, &status);
	return (status);
}
