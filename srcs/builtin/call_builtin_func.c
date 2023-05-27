#include "ft_builtin.h"
#include "minishell.h"
#include "ft_string.h"

//echo, cd, pwd, export, unset, env, exit
bool	is_builtin_func(char *cmd)
{
	if (!cmd)
		return (false);
	if (is_equal_strings(cmd, "echo"))
		return (true);
	if (is_equal_strings(cmd, "cd"))
		return (true);
	if (is_equal_strings(cmd, "pwd"))
		return (true);
	if (is_equal_strings(cmd, "export"))
		return (true);
	if (is_equal_strings(cmd, "unset"))
		return (true);
	if (is_equal_strings(cmd, "env"))
		return (true);
	if (is_equal_strings(cmd, "exit"))
		return (true);
	return (false);
}

int	call_builtin_func(char **command, bool *is_exit_shell)
{
	if (!command)
		return (FATAL_ERROR);
	if (is_equal_strings(command[0], "echo"))
		return (ft_echo(command));
//	if (is_equal_strings(command[0], "cd"))
//		return (true);
//	if (is_equal_strings(command[0], "pwd"))
//		return (true);
//	if (is_equal_strings(command[0], "export"))
//		return (true);
//	if (is_equal_strings(command[0], "unset"))
//		return (true);
//	if (is_equal_strings(command[0], "env"))
//		return (true);
	if (is_equal_strings(command[0], "exit"))
		return (ft_exit(command, is_exit_shell));
	return (FATAL_ERROR);
}
