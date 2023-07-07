#include "ms_exec.h"

void	init_cmd(t_command *cmd, t_deque *dq_cmd)
{
	cmd->head_command = dq_cmd;
	cmd->exec_command = NULL;
	cmd->next_command = NULL;
}

// todo: init pipefd is necessary..?
void	init_fd(t_fd *fd)
{
	fd->pipefd[0] = IN_FD_INIT;
	fd->pipefd[1] = OUT_FD_INIT;
	fd->prev_fd = STDIN_FILENO;
}
