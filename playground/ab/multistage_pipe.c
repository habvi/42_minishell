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

static int	connect_pipe(int unnecessary_fd, int old_fd, int new_fd)
{
	if (x_close(unnecessary_fd) == SYS_ERROR)
		return (EXIT_FAILURE);
	if (x_close(new_fd) == SYS_ERROR)
		return (EXIT_FAILURE);
	if (x_dup2(old_fd, new_fd) == SYS_ERROR)
		return (EXIT_FAILURE);
	if (x_close(old_fd) == SYS_ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	child_proc(int pipefd[2], pid_t pid, char *cmd[], char *next_cmd[])
{
	(void)pid;
	// ft_dprintf(STDERR_FILENO, "===  child process start [PID: %d] ===\n", pid);
	if (*next_cmd)
	{
		if (connect_pipe(pipefd[0], pipefd[1], STDOUT_FILENO) == SYS_ERROR)
			exit(EXIT_FAILURE);
	}
	if (execvp(cmd[0], cmd) == EXECVE_ERROR) // forbidden func
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

static void	parent_proc(int pipefd[2], pid_t pid, char *next_cmd[])
{
	int		status;
	pid_t	wait_pid;
	int		last_exit_status;

	// ft_dprintf(STDERR_FILENO, "=== parent process start [PID: %d] ===\n", pid);
	// last command
	if (*next_cmd == NULL)
	{
		wait_pid = waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
	}
	else
	{
		if (connect_pipe(pipefd[1], pipefd[0], STDIN_FILENO) == SYS_ERROR)
			exit(EXIT_FAILURE);
	}
	// last command
	if (*next_cmd == NULL)
	{
		wait_pid = NOT_END_CHILD_PROC;
		while (wait_pid == NOT_END_CHILD_PROC)
		{
			wait_pid = x_waitpid(P_ALL, &status, WNOHANG);
			if (wait_pid == WAIT_ERROR)
				exit(EXIT_FAILURE);
			if (wait_pid == NOT_END_CHILD_PROC)
				continue ;
			if (WIFEXITED(status))
			{
				ft_dprintf(STDERR_FILENO, "\nchild exit success! pid: %d, status: %d\n", wait_pid, WEXITSTATUS(status));
				exit(WEXITSTATUS(status));
			}
			else
			{
				ft_dprintf(STDERR_FILENO, "\nchild exit failure! pid: %d, status: %d\n", wait_pid, WEXITSTATUS(status));
				exit(WEXITSTATUS(status));
			}
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

	if (argc == 1)
		return (EXIT_SUCCESS);
	cmd = argv + 1;
	next_cmd = cmd;
	while (true)
	{
		next_cmd = move_next_command(next_cmd);
		if (x_pipe(pipefd) == PIPE_ERROR)
			exit(EXIT_FAILURE);
		pid = x_fork();
		if (pid == FORK_ERROR)
			exit(EXIT_FAILURE);
		if (pid == CHILD_PID)
			child_proc(pipefd, pid, cmd, next_cmd);
		else
			parent_proc(pipefd, pid, next_cmd);
		cmd = next_cmd;
	}
	return (EXIT_SUCCESS);
}

// ./a.out "echo" "-e" "aaa\naacc\nbbb\nbbcc\nccc\naabb\nabc" "|" "grep" "a" "|" "grep" "c"