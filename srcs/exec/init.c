#include "minishell.h"
#include "ms_exec.h"

// todo: init pipefd is necessary..?
void	init_fd(t_fd *fd)
{
	fd->pipefd[0] = IN_FD_INIT;
	fd->pipefd[1] = OUT_FD_INIT;
	fd->prev_fd = STDIN_FILENO;
}
