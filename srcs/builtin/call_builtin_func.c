#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ft_deque.h"
#include "ft_string.h"

bool	is_single_builtin(t_deque_node *node)
{
	if (!node)
		return (false);
	if (!is_command_builtin((const char *)node->content))
		return (false);
	if (count_pipe(node) > 0)
		return (false);
	return (true);
}

//echo, cd, pwd, export, unset, env, exit
bool	is_command_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	if (is_equal_strings(cmd, STR_ECHO))
		return (true);
	if (is_equal_strings(cmd, STR_CD))
		return (true);
	if (is_equal_strings(cmd, STR_PWD))
		return (true);
	if (is_equal_strings(cmd, STR_EXPORT))
		return (true);
	if (is_equal_strings(cmd, STR_UNSET))
		return (true);
	if (is_equal_strings(cmd, STR_ENV))
		return (true);
	if (is_equal_strings(cmd, STR_EXIT))
		return (true);
	return (false);
}

int	call_builtin_func(const char **command, bool *is_exit_shell)
{
	if (!command)
		return (FATAL_ERROR);
	if (is_equal_strings(command[0], STR_ECHO))
		return (ft_echo(command));
//	if (is_equal_strings(command[0], STR_CD))
//		return (true);
//	if (is_equal_strings(command[0], STR_PWD))
//		return (true);
//	if (is_equal_strings(command[0], STR_EXPORT))
//		return (true);
//	if (is_equal_strings(command[0], STR_UNSET))
//		return (true);
//	if (is_equal_strings(command[0], STR_ENV))
//		return (true);
	if (is_equal_strings(command[0], STR_EXIT))
		return (ft_exit(command, is_exit_shell));
	return (FATAL_ERROR);
}
