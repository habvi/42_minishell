#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"

uint8_t	call_builtin_command(const char *const *argv, t_context *context)
{
	if (ft_streq(argv[0], CMD_ECHO))
		return (ft_echo(argv));
	if (ft_streq(argv[0], CMD_CD))
		return (ft_cd(argv, context));
	if (ft_streq(argv[0], CMD_PWD))
		return (ft_pwd(argv, context));
	if (ft_streq(argv[0], CMD_EXPORT))
		return (ft_export(argv, context));
	if (ft_streq(argv[0], CMD_UNSET))
		return (ft_unset(argv, context));
	if (ft_streq(argv[0], CMD_ENV))
		return (ft_env(argv, context->env));
	if (ft_streq(argv[0], CMD_EXIT))
		return (ft_exit(argv, context));
	return (UNREACHABLE);
}
