#include "minishell.h"
#include "ft_dprintf.h"
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

static int	handle_child_pipes(t_command *cmd, t_fd *fd)
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

// use PROMPT_NAME
void	child_process(t_command *cmd, t_fd *fd, char **environ)
{
	char	**command;

	command = cmd->exec_command;
	// debug_func(__func__, __LINE__);
	// debug_2d_array(command);
	// if (!command[0])
	// 	exit(EXIT_SUCCESS);
	if (handle_child_pipes(cmd, fd) == PROCESS_ERROR)
		exit(EXIT_FAILURE);
	if (execve(command[0], command, environ) == EXECVE_ERROR)
	{
		// write or malloc error..?
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", \
											command[0], EXIT_MSG_NO_SUCH_FILE);
		perror("execve");
		// leaks
		free_2d_array(&cmd->head);
		exit(EXIT_CODE_NO_SUCH_FILE);
	}
}
