#include "ms_builtin.h"
#include "ft_string.h"

//echo, cd, pwd, export, unset, env, exit
bool	is_command_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_streq(cmd, CMD_CD))
		return (true);
	if (ft_streq(cmd, CMD_DECLARE))
		return (true);
	if (ft_streq(cmd, CMD_ECHO))
		return (true);
	if (ft_streq(cmd, CMD_ENV))
		return (true);
	if (ft_streq(cmd, CMD_EXIT))
		return (true);
	if (ft_streq(cmd, CMD_EXPORT))
		return (true);
	if (ft_streq(cmd, CMD_PWD))
		return (true);
	if (ft_streq(cmd, CMD_UNSET))
		return (true);
	return (false);
}
