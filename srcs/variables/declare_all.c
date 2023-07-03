#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_dprintf.h"

void	declare_all(const char *const *args, \
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
			// todo: func
			ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n", \
				SHELL_NAME, CMD_EXPORT, args[i], ERROR_MSG_NOT_VALID_ID);
		}
		i++;
	}
}
