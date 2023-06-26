#include "minishell.h"
#include "ms_exec.h"
#include "ft_sys.h"

static t_result	handle_parent_pipes_except_first(t_fd *fd)
{
	if (x_close(fd->prev_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

static t_result	handle_parent_pipes_except_last(t_fd *fd)
{
	fd->prev_fd = fd->pipefd[READ];
	if (x_close(fd->pipefd[WRITE]) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

t_result	handle_parent_pipes(t_command *cmd, t_fd *fd)
{
	if (!is_first_command(fd->prev_fd))
	{
		if (handle_parent_pipes_except_first(fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (!is_last_command(cmd->next_command))
	{
		if (handle_parent_pipes_except_last(fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
