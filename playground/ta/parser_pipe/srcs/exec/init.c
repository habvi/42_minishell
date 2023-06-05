#include "minishell.h"

void	init_cmd(t_command *cmd, t_deque *dq_cmd)
{
	cmd->head_command = dq_cmd;
	cmd->exec_command = NULL;
	cmd->next_command = NULL;
}

// need..?
void	init_fd(t_fd *fd)
{
	fd->pipefd[0] = 0;
	fd->pipefd[1] = 0;
	fd->prev_fd = STDIN_FILENO;
}
