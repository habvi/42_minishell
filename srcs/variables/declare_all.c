#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"

void	var_declare_all(const char *const *args, \
						t_var *var, \
						uint8_t *status, \
						t_var_attr attr)
{
	size_t		i;
	t_result	result;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		result = var_declare_arg(args[i], var, attr);
		if (result == FAILURE)
		{
			*status = NOT_A_VALID_IDENTIFIER;
			puterr_cmd_quoted_arg_msg(CMD_EXPORT, \
										args[i], \
										ERROR_MSG_NOT_VALID_ID);
		}
		i++;
	}
}
