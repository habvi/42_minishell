#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"

int	call_builtin_command(char *const *argv, t_params *params)
{
	if (!argv)
		return (FATAL_ERROR);
	if (ft_streq(argv[0], CMD_ECHO))
		return (ft_echo(argv));
//	if (ft_streq(argv[0], CMD_CD))
//		return (true);
//	if (ft_streq(argv[0], CMD_PWD))
//		return (true);
	if (ft_streq(argv[0], CMD_EXPORT))
		return (ft_export(argv, params));
	if (ft_streq(argv[0], CMD_UNSET))
		return (ft_unset(argv, params));
	if (ft_streq(argv[0], CMD_ENV))
		return (ft_env(argv, params));
	if (ft_streq(argv[0], CMD_EXIT))
		return (ft_exit(argv, params));
	return (UNREACHABLE);
}
