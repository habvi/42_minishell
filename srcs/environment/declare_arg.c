#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"
#include "ft_dprintf.h"

int	declare_arg(const char *const arg, t_env *env, int *status)
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
		*status = NOT_A_VALID_IDENTIFIER;
		ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n", \
			SHELL_NAME, CMD_EXPORT, arg, ERROR_MSG_NOT_VALID_ID); // todo: func
		return (SUCCESS);
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
