#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"

static void	declare_all(const char *const *args, t_env *env, uint8_t *status)
{
	size_t	i;
	int		result;

	i = 0;
	while (args[i])
	{
		result = declare_arg(args[i], env);
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

static void	declare_to_env(const char *const *argv, t_env *env, uint8_t *status)
{
	if (is_option(argv[1]))
	{
		*status = INVALID_OPTION;
		// todo: func
		ft_dprintf(STDERR_FILENO, \
				"%s: %s: %c%c: %s\n", \
					SHELL_NAME, \
					CMD_EXPORT, \
					CMD_OPTION_MARKER, argv[1][1], \
					ERROR_MSG_INVALID_OP);
		return ;
	}
	declare_all(&argv[1], env, status);
}

uint8_t	ft_export(const char *const *argv, t_params *params)
{
	const size_t	argc = count_argv(argv);
	uint8_t			status;

	status = EXIT_SUCCESS;
	if (argc == 1)
	{
		params->env->print_detail(params->env);
		return (status);
	}
	declare_to_env(argv, params->env, &status);
	return (status);
}
