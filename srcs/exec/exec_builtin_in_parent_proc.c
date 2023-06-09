#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ft_deque.h"
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
//	if (ft_streq(command[0], CMD_UNSET))
//		return (true);
//	if (ft_streq(command[0], CMD_ENV))
//		return (true);
	if (ft_streq(command[0], CMD_EXIT))
		return (ft_exit(command, params));
	return (UNREACHABLE);
}

int	exec_builtin_in_parent_proc(t_command cmd, \
								t_deque_node *exec_cmd, \
								t_params *params)
{
	int		status;
	size_t	cmd_size;

	cmd.next_command = get_next_command(exec_cmd, &cmd_size);
	cmd.exec_command = convert_command_to_array(exec_cmd, cmd_size);
	status = call_builtin_command(cmd.exec_command, params);
	free_2d_array(&cmd.exec_command);
	return (status);
}
