#include "ft_builtin.h"
#include "minishell.h"
#include "ft_string.h"

//echo, cd, pwd, export, unset, env, exit
bool	is_builtin_func(char *cmd)
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

int	call_builtin_func(char **command, bool *is_exit_shell)
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
<<<<<<< HEAD
	if (is_equal_strings(command[0], "exit"))
		return (ft_exit((const char **)command, is_exit_shell));
=======
	if (is_equal_strings(command[0], STR_EXIT))
		return (ft_exit(command, is_exit_shell));
>>>>>>> 9fa0d9e (update(calc_builtin): command str in header)
	return (FATAL_ERROR);
}
