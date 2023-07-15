#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"

static void	unset_args(const char *const *args, t_var *var, uint8_t *status)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (is_valid_key(args[i]))
			var->unset(var, args[i]);
		else
		{
			*status = NOT_A_VALID_IDENTIFIER;
			puterr_cmd_arg_msg(CMD_UNSET, args[i], ERROR_MSG_NOT_VALID_ID);
		}
		i++;
	}
}

uint8_t	ft_unset(const char *const *argv, t_var *var)
{
	uint8_t	status;
	size_t	i;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	unset_args(&argv[i], var, &status);
	return (status);
}
