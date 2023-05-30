#include "deque.h"
#include "ft_builtin.h"
#include "ft_string.h"
#include "exec.h"

size_t	count_pipe(t_deque_node *node)
{
	size_t	cnt;

	cnt = 0;
	while (node)
	{
		if (is_equal_strings(node->content, "|"))
			cnt++;
		node = node->next;
	}
	return (cnt);
}

int	exec_builtin_in_parent_proc(t_command cmd, t_deque_node *node, \
								bool *is_exit_shell)
{
	int		status;
	size_t	cmd_size;

	cmd.next_command = get_next_command(node, &cmd_size);
	cmd.exec_command = convert_command_to_array(node, cmd_size);
	status = call_builtin_func((const char **)cmd.exec_command, is_exit_shell);
	free_2d_array(&cmd.exec_command);
	return (status);
}
