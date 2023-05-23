#include "minishell.h"
#include "libft.h"

static int	handle_parent_pipes_except_first(t_fd *fd)
{
	if (x_close(fd->prev_fd) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (EXIT_SUCCESS);
}

static int	handle_parent_pipes_except_last(t_fd *fd)
{
	fd->prev_fd = fd->pipefd[READ];
	if (x_close(fd->pipefd[WRITE]) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (EXIT_SUCCESS);
}

int	handle_parent_pipes(t_command *cmd, t_fd *fd)
{
	if (!is_first_command(fd->prev_fd))
	{
		if (handle_parent_pipes_except_first(fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (!is_last_command(*cmd->next_command))
	{
		if (handle_parent_pipes_except_last(fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (EXIT_SUCCESS);
}
