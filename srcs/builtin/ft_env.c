#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"

// {"env", "arg1", "arg2", ..., NULL};
int	ft_env(char *const *argv, t_params *params)
{
	const size_t	argc = count_argc(argv);

	if (argc != 1)
	{
		// todo : error handring
		return (FAILURE);
	}
	params->env->print(params->env);
	return (SUCCESS);
}
