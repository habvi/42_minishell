#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"
#include "ms_var.h"

static bool	is_valid_option_for_env(const char *const *argv, uint8_t *status, size_t *i)
{
	if (is_option(argv[*i], CMD_OPTION_MARKER))
	{
		*status = ENV_INVALID_OPTION;
		// puterr_env_option(argv[*i]);
		return (false);
	}
	if (is_end_of_option(argv[*i]))
		(*i)++;
	return (true);
}

// {"env", "arg1", "arg2", ..., NULL};
uint8_t	ft_env(const char *const *argv, t_var *var)
{
	uint8_t	status;
	size_t	i;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option_for_env(argv, &status, &i))
		return (status);
	if ((argv[i] && !ft_streq(argv[i], "-")) || (argv[i] && argv[i + 1]))
	{
		status = TOO_MANY_ARG_STATUS;
		// puterr_env_argument(argv[i]);
		return (status);
	}
	if (ft_streq(argv[i], "-"))
		return (status);
	var->env_print(var);
	return (status);
}
