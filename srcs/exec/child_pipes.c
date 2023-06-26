#include "minishell.h"
#include "ms_exec.h"
#include "ft_sys.h"

static t_result	handle_child_pipes_except_first(t_fd *fd)
{
	if (x_close(STDIN_FILENO) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	if (x_dup2(fd->prev_fd, STDIN_FILENO) == DUP_ERROR)
		return (PROCESS_ERROR);
	if (x_close(fd->prev_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

static t_result	handle_child_pipes_except_last(t_fd *fd)
{
	if (x_close(fd->pipefd[READ]) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	if (x_close(STDOUT_FILENO) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	if (x_dup2(fd->pipefd[WRITE], STDOUT_FILENO) == DUP_ERROR)
		return (PROCESS_ERROR);
	if (x_close(fd->pipefd[WRITE]) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

//todo:fds?
t_result	handle_child_pipes(t_command *cmd, t_fd *fd)
{
	if (!is_first_command(fd->prev_fd))
	{
		if (handle_child_pipes_except_first(fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (!is_last_command(cmd->next_command))
	{
		if (handle_child_pipes_except_last(fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
