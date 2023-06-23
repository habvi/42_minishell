#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"

static int	declare_all(const char *const *args, t_env *env, int *status)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (declare_arg(args[i], env, status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	declare_to_env(const char *const *argv, t_env *env, int *status)
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
		return (SUCCESS);
	}
	if (declare_all(&argv[1], env, status) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

int	ft_export(const char *const *argv, t_params *params)
{
	const size_t	argc = count_argv(argv);
	int				status;

	status = EXIT_SUCCESS;
	if (argc == 1)
	{
		params->env->print_detail(params->env);
		return (status);
	}
	// todo: if status is unsigned, can't express PROCESS_ERROR
	if (declare_to_env(argv, params->env, &status) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (status);
}
