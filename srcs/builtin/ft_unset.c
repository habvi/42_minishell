#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"

static bool	is_option(const char *word)
{
	return (word[0] == '-' && word[1]);
}

int	ft_unset(char *const *argv, t_params *params)
{
	const size_t	argc = count_argv(argv);
	size_t			i;
	int				status;

	if (argc == 1)
		return (SUCCESS);
	if (is_option(argv[1]))
	{
		status = INVALID_OPTION; // print error
		return (status);
	}
	status = SUCCESS;
	i = 1;
	while (argv[i])
	{
		if (is_valid_key(argv[i]))
			params->env->unset(params->env, argv[i]);
		else
			status = NOT_A_VALID_IDENTIFIER; // print error
		i++;
	}
	return (status);
}
