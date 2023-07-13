#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_sys.h"

static t_result	connect_prev_fd_to_stdin(int prev_fd, int proc_fd_in)
{
	if (proc_fd_in == IN_FD_INIT) // no redirect in file
	{
		if (x_close(STDIN_FILENO) == CLOSE_ERROR)
			return (PROCESS_ERROR);
		if (x_dup2(prev_fd, STDIN_FILENO) == DUP_ERROR)
			return (PROCESS_ERROR);
	}
	if (x_close(prev_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

static t_result	connect_stdout_to_pipe(int pipe_fd[2], int proc_fd_out)
{
	if (x_close(pipe_fd[READ]) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	if (proc_fd_out == OUT_FD_INIT) // no redirect out file
	{
		if (x_close(STDOUT_FILENO) == CLOSE_ERROR)
			return (PROCESS_ERROR);
		if (x_dup2(pipe_fd[WRITE], STDOUT_FILENO) == DUP_ERROR)
			return (PROCESS_ERROR);
	}
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

	if (!is_first_command(prev_fd)) // prev_fd != IN_FD_INIT
	{
		if (connect_prev_fd_to_stdin(prev_fd, self_node->proc_fd[IN]) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (!is_last_command_node(self_node))
	{
		if (connect_stdout_to_pipe(self_node->pipe_fd, self_node->proc_fd[OUT]) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
