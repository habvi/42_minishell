#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_dprintf.h"

// export declare VAR_ENV
static void	declare_all(const char *const *args, t_env *env, uint8_t *status)
{
	size_t		i;
	t_result	result;

	i = 0;
	while (args[i])
	{
		result = env_declare_arg(args[i], env, VAR_ENV);
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

uint8_t	ft_export(const char *const *argv, t_env *env)
{
	uint8_t	status;
	size_t	i;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	if (!argv[i])
	{
		env->print_detail(env, VAR_ENV);
		return (status);
	}
	declare_all(&argv[i], env, &status);
	return (status);
}
