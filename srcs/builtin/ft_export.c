#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"

static int	declare_arg(const char *const arg, t_env *env, int *status)
{
	int			result;
	char		*key;
	char		*value;
	t_env_op	op;

	result = separate_env_variables(arg, &key, &value, &op);
	if (result == PROCESS_ERROR)
		return (result);
	if (result == FAILURE)
	{
		*status = NOT_A_VALID_IDENTIFIER; // todo: print error
		return (result);
	}
	if (result == CONTINUE)
		return (SUCCESS);
	if (env->set(env, key, value, op) == FAILURE) // todo: PROCESS_ERROR
	{
		ft_free(key);
		ft_free(value);
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

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
	*status = SUCCESS;
	if (is_option(argv[1]))
	{
		*status = INVALID_OPTION; // todo:print error
		return (*status);
	}
	if (declare_all(&argv[1], env, status) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

int	ft_export(const char *const *argv, t_params *params)
{
	const size_t	argc = count_argv(argv);
	int				status;

	status = SUCCESS;
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
