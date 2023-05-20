#include <unistd.h> // fork
#include <sys/wait.h> // wait
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "libft.h"
#include "ft_dprintf.h"
#include "test.h"

extern char	**environ;

// static int	connect_pipe(int unnecessary_fd, int old_fd, int new_fd)
// {
// 	if (x_close(unnecessary_fd) == SYS_ERROR)
// 		return (EXIT_FAILURE);
// 	if (x_close(new_fd) == SYS_ERROR)
// 		return (EXIT_FAILURE);
// 	if (x_dup2(old_fd, new_fd) == SYS_ERROR)
// 		return (EXIT_FAILURE);
// 	if (x_close(old_fd) == SYS_ERROR)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

static void	exit_success(int status, int last_cmd_status)
{
	ft_dprintf(STDERR_FILENO, "\nchild exit success! status: %d, last cmd exit status: %d\n", status, last_cmd_status);
	exit(last_cmd_status);
}

static void	exit_failure(char *err)
{
	ft_dprintf(STDERR_FILENO, "\nchild exit failure!");
	perror(err);
	exit(EXIT_FAILURE);
}

static bool	is_last_command(char *next_cmd)
{
	return (!next_cmd);
}

static void	child_proc(int pipefd[2], char **cmd, char **next_cmd, int prev_fd)
{
	if (!is_last_command(*next_cmd))
	{
		// handle SYS_ERROR >>>
		close(STDIN_FILENO);
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);

		close(pipefd[READ]);
		close(STDOUT_FILENO);
		dup2(pipefd[WRITE], STDOUT_FILENO);
		close(pipefd[WRITE]);
		// <<< handle SYS_ERROR
	}
	if (execvp(cmd[0], cmd) == EXECVE_ERROR) // forbidden func
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

static void	parent_proc(int pipefd[2], pid_t pid, char **next_cmd, int *prev_fd)
{
	int		status;
	pid_t	wait_pid;
	int		last_cmd_status;

	ft_dprintf(STDERR_FILENO, "=== parent process [child pid: %d] ===\n", pid);
	if (!is_last_command(*next_cmd))
	{
		// handle SYS_ERROR >>>
		close(pipefd[WRITE]);
		close(*prev_fd);
		*prev_fd = dup(pipefd[READ]);
		close(pipefd[READ]);
		// <<< handle SYS_ERROR
		return ;
	}
	wait_pid = waitpid(pid, &status, 0);
	// ft_dprintf(STDERR_FILENO, "last wait_pid: %d\n", wait_pid);
	if (WIFEXITED(status))
		last_cmd_status = WEXITSTATUS(status);
	else
		exit_failure("waitpid");
	while (true)
	{
		wait_pid = wait(NULL);
		// ft_dprintf(STDERR_FILENO, "wait_pid: %d\n", wait_pid);
		// wait_pid = waitpid(P_ALL, &status, WNOHANG);
		if (wait_pid == WAIT_ERROR)
		{
			if (errno == ECHILD && WIFEXITED(status))
				exit_success(WEXITSTATUS(status), last_cmd_status);
			else
				exit_failure("wait");
		}
	}
}

// move next_cmd after "|"
static char	**move_next_command(char **next_cmd)
{
	while (*next_cmd && strcmp(*next_cmd, "|") != 0)
		next_cmd++;
	if (*next_cmd != NULL)
	{
		*next_cmd = NULL;
		next_cmd++;
	}
	return (next_cmd);
}

// pipefd[0]:read, pipefd[1]:write
int	main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	pid;
	char	**cmd;
	char	**next_cmd;
	int		prev_fd;

	if (argc == 1)
		return (EXIT_SUCCESS);
	cmd = argv + 1;
	next_cmd = cmd;
	prev_fd = STDIN_FILENO;
	while (true)
	{
		next_cmd = move_next_command(next_cmd);
		if (x_pipe(pipefd) == PIPE_ERROR)
			exit(EXIT_FAILURE);
		pid = x_fork();
		if (pid == FORK_ERROR)
			exit(EXIT_FAILURE);
		if (pid == CHILD_PID)
			child_proc(pipefd, cmd, next_cmd, prev_fd);
		else
			parent_proc(pipefd, pid, next_cmd, &prev_fd);
		cmd = next_cmd;
	}
	return (EXIT_SUCCESS);
}

// ./a.out "echo" "-e" "aaa\naacc\nbbb\nbbcc\nccc\naabb\nabc" "|" "grep" "a" "|" "grep" "c"