#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_sys.h"

static t_result	handle_child_pipes_except_first(int prev_fd)
{
	if (x_close(STDIN_FILENO) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	if (x_dup2(prev_fd, STDIN_FILENO) == DUP_ERROR)
		return (PROCESS_ERROR);
	if (x_close(prev_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

static t_result	handle_child_pipes_except_last(int pipe_fd[2])
{
	ft_dprintf(2, "----------------------\n");
	if (x_close(pipe_fd[READ]) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	if (x_close(STDOUT_FILENO) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	if (x_dup2(pipe_fd[WRITE], STDOUT_FILENO) == DUP_ERROR)
		return (PROCESS_ERROR);
	if (x_close(pipe_fd[WRITE]) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

bool	is_first_command(int prev_fd)
{
	return (prev_fd == IN_FD_INIT);
}

t_result	handle_child_pipes(t_ast *self_node)
{
	const int	prev_fd = self_node->prev_fd;

	if (!is_first_command(prev_fd))
	{
		// ft_dprintf(2, "-- first command ------\n");
		if (handle_child_pipes_except_first(prev_fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (!is_last_command_node(self_node))
	{
		if (handle_child_pipes_except_last(self_node->pipe_fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	// char c;
	// while (read(self_node->pipe_fd[WRITE], &c, 1) > 0)
	// {
	// 	write(2, &c, 1);
	// }
	// ft_dprintf(2, "[%s/%d]\n", get_head_token_str(self_node->command), self_node->prev_fd);
	return (SUCCESS);
}
