#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"

int	call_builtin_command(char *const *command, t_params *params)
{
	if (!command)
		return (FATAL_ERROR);
	if (ft_streq(command[0], CMD_ECHO))
		return (ft_echo(command));
//	if (ft_streq(command[0], CMD_CD))
//		return (true);
//	if (ft_streq(command[0], CMD_PWD))
//		return (true);
//	if (ft_streq(command[0], CMD_EXPORT))
//		return (true);
	if (ft_streq(command[0], CMD_UNSET))
		return (ft_unset(command, params));
	if (ft_streq(command[0], CMD_ENV))
		return (ft_env(command, params));
	if (ft_streq(command[0], CMD_EXIT))
		return (ft_exit(command, params));
	return (UNREACHABLE);
}
