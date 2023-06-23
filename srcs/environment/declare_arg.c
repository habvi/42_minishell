#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"

void	declare_arg(const char *const arg, t_env *env, uint8_t *status)
{
	int			result;
	char		*key;
	char		*value;
	t_env_op	op;

	result = separate_env_variables(arg, &key, &value, &op);
	if (result == FAILURE)
	{
		*status = NOT_A_VALID_IDENTIFIER;
		ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n", \
			SHELL_NAME, CMD_EXPORT, arg, ERROR_MSG_NOT_VALID_ID); // todo: func
		return ;
	}
	if (result == CONTINUE)
		return ;
	env->set(env, key, value, op);
}
