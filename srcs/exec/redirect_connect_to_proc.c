#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_sys.h"

static t_result	connect_redirect_in_to_proc(int *prev_fd, int in_fd)
{
	if (*prev_fd != IN_FD_INIT)
	{
		if (x_close(*prev_fd) == CLOSE_ERROR)
			return (PROCESS_ERROR);
		*prev_fd = IN_FD_INIT;
	}
	if (x_close(STDIN_FILENO) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	if (x_dup2(in_fd, STDIN_FILENO) == DUP_ERROR)
		return (PROCESS_ERROR);
	if (x_close(in_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

static t_result	connect_redirect_out_to_proc(int out_fd)
{
	if (x_close(STDOUT_FILENO) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	if (x_dup2(out_fd, STDOUT_FILENO) == DUP_ERROR)
		return (PROCESS_ERROR);
	if (x_close(out_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

bool	is_use_redirect_in(int proc_in_fd)
{
	return (proc_in_fd != IN_FD_INIT);
}

bool	is_use_redirect_out(int proc_out_fd)
{
	return (proc_out_fd != OUT_FD_INIT);
}

t_result	connect_redirect_to_proc(t_ast *self_node)
{
	if (is_use_redirect_in(self_node->proc_fd[IN]))
	{
		if (connect_redirect_in_to_proc(\
			&self_node->prev_fd, self_node->proc_fd[IN]) == PROCESS_ERROR)
		{
			close_proc_out_fd(&self_node->proc_fd[OUT]);
			return (PROCESS_ERROR);
		}
//		self_node->proc_fd[IN] = REDIRECT_USED;
	}
	if (is_use_redirect_out(self_node->proc_fd[OUT]))
	{
		if (connect_redirect_out_to_proc(\
			self_node->proc_fd[OUT]) == PROCESS_ERROR)
		{
			close_proc_in_fd(&self_node->proc_fd[IN]);
			return (PROCESS_ERROR);
		}
//		self_node->proc_fd[OUT] = REDIRECT_USED;
	}
	return (SUCCESS);
}
