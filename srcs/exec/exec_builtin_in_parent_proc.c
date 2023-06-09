#include "ms_builtin.h"
#include "ms_exec.h"
#include "ft_deque.h"
#include "ft_string.h"

size_t	count_pipe(t_deque_node *cmd)
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
