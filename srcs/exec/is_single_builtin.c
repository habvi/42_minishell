#include "ms_builtin.h"
#include "ft_deque.h"
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

static size_t	count_pipe(t_deque_node *cmd)
{
	size_t	cnt;

	cnt = 0;
	while (cmd)
	{
		if (ft_streq(cmd->content, "|"))
			cnt++;
		cmd = cmd->next;
	}
	return (cnt);
}

bool	is_single_builtin(t_deque_node *cmd)
{
	if (!cmd)
		return (false);
	if (!is_command_builtin((const char *)cmd->content))
		return (false);
	if (count_pipe(cmd) > 0)
		return (false);
	return (true);
}
