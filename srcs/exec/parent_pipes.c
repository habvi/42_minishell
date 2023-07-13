#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_sys.h"

static t_result	close_prev_fd(int prev_fd)
{
	if (x_close(prev_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

static t_result	copy_pipe_read_for_next(t_ast *self_node)
{
	if (self_node->parent)
		self_node->parent->prev_fd = self_node->pipe_fd[READ]; // parent_prev
	if (x_close(self_node->pipe_fd[WRITE]) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

t_result	handle_parent_pipes(t_ast *self_node)
{
	const int	prev_fd = self_node->prev_fd;

	if (!is_first_command(prev_fd))
	{
		if (close_prev_fd(prev_fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (!is_last_command_node(self_node))
	{
		if (copy_pipe_read_for_next(self_node) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	// todo: error
	if (is_last_command_node(self_node))
	{
//		ft_dprintf(2, "%s cmd:%s\n", __func__, get_head_token_str(self_node->command));
		if (self_node->pipe_fd[READ] != IN_FD_INIT)
			x_close(self_node->pipe_fd[READ]);
		if (self_node->pipe_fd[WRITE] != OUT_FD_INIT)
			x_close(self_node->pipe_fd[WRITE]);
	}
	return (SUCCESS);
}
