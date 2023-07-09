#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_sys.h"

static t_result	handle_parent_pipes_except_first(int prev_fd)
{
	if (x_close(prev_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

static t_result	handle_parent_pipes_except_last(t_ast *self_node)
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
		if (handle_parent_pipes_except_first(prev_fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (!is_last_command_node(self_node))
	{
		if (handle_parent_pipes_except_last(self_node) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
