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

// todo: parent?
static t_result	handle_parent_pipes_except_last(t_ast *self_node)
{
	if (self_node->parent)
	{
		// ft_dprintf(2, "1 prev_fd : %d\n", self_node->parent->prev_fd);
		self_node->parent->prev_fd = self_node->pipe_fd[READ]; // parent_prev
		// ft_dprintf(2, "2 prev_fd : %d\n", self_node->parent->prev_fd);
	}
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
	// ft_dprintf(2, "3 pipe_fd : %d, %d\n", self_node->pipe_fd[0], self_node->pipe_fd[1]);
	return (SUCCESS);
}
