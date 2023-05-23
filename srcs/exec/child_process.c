#include "minishell.h"
#include "ft_dprintf.h"
#include "libft.h"

// use PROMPT_NAME
void	child_process(t_command *cmd, t_fd *fd, char **environ)
{
	char	**command;

	command = cmd->exec_command;
	debug_func(__func__, __LINE__);
	debug_2d_array(command);
	// if (!command[0])
	// 	exit(EXIT_SUCCESS);
	if (!is_first_command(fd->prev_fd))
 	{
		// SYS_ERROR
		close(STDIN_FILENO);
		dup2(fd->prev_fd, STDIN_FILENO);
		close(fd->prev_fd);
	}
	if (!is_last_command(*cmd->next_command))
	{
		// SYS_ERROR
		close(fd->pipefd[READ]);
		close(STDOUT_FILENO);
		dup2(fd->pipefd[WRITE], STDOUT_FILENO);
		close(fd->pipefd[WRITE]);
	}
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
