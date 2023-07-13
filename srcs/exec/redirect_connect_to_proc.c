#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_sys.h"

void	connect_redirect_to_proc(t_ast *self_node)
{
	if (self_node->proc_fd[IN] != IN_FD_INIT)
	{
		if (self_node->prev_fd != IN_FD_INIT)
			x_close(self_node->prev_fd); // todo: error
		self_node->prev_fd = IN_FD_INIT;

		x_close(STDIN_FILENO);
		x_dup2(self_node->proc_fd[IN], STDIN_FILENO);
		x_close(self_node->proc_fd[IN]);
	}
	if (self_node->proc_fd[OUT] != OUT_FD_INIT)
	{
		x_close(STDOUT_FILENO);
		x_dup2(self_node->proc_fd[OUT], STDOUT_FILENO);
		x_close(self_node->proc_fd[OUT]);
	}
}
