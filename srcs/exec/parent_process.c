#include <sys/wait.h> // wait
#include <errno.h> // ECHILD
#include "minishell.h"
#include "ft_dprintf.h"
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

static int	handle_parent_pipes(t_command *cmd, t_fd *fd)
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

static int	get_last_command_status(pid_t pid, int *status, int *last_exit_status)
{
	pid_t	wait_pid;

	wait_pid = x_waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*last_exit_status = WEXITSTATUS(*status);
	else
		return (WAIT_ERROR);
	return (EXIT_SUCCESS);
}

static int	wait_all_child_process(int status)
{
	while (true)
	{
		if (wait(NULL) != WAIT_ERROR)
			continue ;
		if (errno == ECHILD && WIFEXITED(status))
			return (EXIT_SUCCESS);
		else
		{
			perror("wait");
			return (PROCESS_ERROR);
		}
	}
	return (EXIT_SUCCESS);
}

int	parent_process(t_command *cmd, t_fd *fd, pid_t pid, int *last_exit_status)
{
	int	status;

	if (handle_parent_pipes(cmd, fd) == PROCESS_ERROR)
		exit(EXIT_FAILURE);
	if (get_last_command_status(pid, &status, last_exit_status) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (wait_all_child_process(status) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	ft_dprintf(STDERR_FILENO, "\nchild exit success!\n");
	ft_dprintf(STDERR_FILENO, "status: %d, exit status: %d\n", \
								WIFEXITED(status), last_exit_status);
	return (EXIT_SUCCESS);
}
