#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_sys.h"

t_result	connect_redirect_to_proc(t_ast *self_node)
{
	if (self_node->proc_fd[IN] != IN_FD_INIT)
	{
		if (self_node->prev_fd != IN_FD_INIT)
		{
			if (x_close(self_node->prev_fd) == CLOSE_ERROR) // todo: error
				return (PROCESS_ERROR);
		}
		self_node->prev_fd = IN_FD_INIT;
		if (x_close(STDIN_FILENO) == CLOSE_ERROR)
			return (PROCESS_ERROR);
		if (x_dup2(self_node->proc_fd[IN], STDIN_FILENO) == DUP_ERROR)
			return (PROCESS_ERROR);
		if (x_close(self_node->proc_fd[IN]) == CLOSE_ERROR)
			return (PROCESS_ERROR);
	}
	if (self_node->proc_fd[OUT] != OUT_FD_INIT)
	{
		if (x_close(STDOUT_FILENO) == CLOSE_ERROR)
			return (PROCESS_ERROR);
		if (x_dup2(self_node->proc_fd[OUT], STDOUT_FILENO) == DUP_ERROR)
			return (PROCESS_ERROR);
		if (x_close(self_node->proc_fd[OUT]) == CLOSE_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
