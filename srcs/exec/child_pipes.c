#include "minishell.h"
#include "libft.h"

static int	handle_child_pipes_except_first(t_fd *fd)
{
	if (x_close(STDIN_FILENO) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (x_dup2(fd->prev_fd, STDIN_FILENO) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (x_close(fd->prev_fd) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (EXIT_SUCCESS);
}

static int	handle_child_pipes_except_last(t_fd *fd)
{
	if (x_close(fd->pipefd[READ]) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (x_close(STDOUT_FILENO) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (x_dup2(fd->pipefd[WRITE], STDOUT_FILENO) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (x_close(fd->pipefd[WRITE]) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (EXIT_SUCCESS);
}

int	handle_child_pipes(t_command *cmd, t_fd *fd)
{
	if (!is_first_command(fd->prev_fd))
	{
		if (handle_child_pipes_except_first(fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	if (!is_last_command(*cmd->next_command))
	{
		if (handle_child_pipes_except_last(fd) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (EXIT_SUCCESS);
}
