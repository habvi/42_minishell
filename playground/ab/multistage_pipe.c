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

static void	child_proc(int pipefd[2], pid_t pid, char *cmd[])
{
	(void)pid;
	// ft_dprintf(STDERR_FILENO, "===  child process start [PID: %d] ===\n", pid);
	if (x_close(pipefd[0]) == SYS_ERROR)
		exit(EXIT_FAILURE);
	if (x_close(STDOUT_FILENO) == SYS_ERROR)
		exit(EXIT_FAILURE);
	if (x_dup2(pipefd[1], STDOUT_FILENO) == SYS_ERROR)
		exit(EXIT_FAILURE);
	if (x_close(pipefd[1]) == SYS_ERROR)
		exit(EXIT_FAILURE);
	if (execvp(cmd[0], cmd) == EXECVE_ERROR) // forbidden func
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

static void	read_and_print(int fd)
{
	const size_t	BUF_SIZE = 50;
	char			buf[BUF_SIZE + 1];
	ssize_t			rsize;

	while (true)
	{
		rsize = x_read(fd, buf, 50);
		if (rsize == READ_ERROR)
			return ;
		if (rsize == 0)
			break ;
		buf[rsize] = '\0';
		printf("%s", buf);
	}
}

static void	parent_proc(int pipefd[2], pid_t pid, char *next_cmd[])
{
	int		status;
	pid_t	wait_pid;

	(void)pid;
	// ft_dprintf(STDERR_FILENO, "=== parent process start [PID: %d] ===\n", pid);
	if (x_close(pipefd[1]) == SYS_ERROR)
		exit(EXIT_FAILURE);
	if (x_close(STDIN_FILENO) == SYS_ERROR)
		exit(EXIT_FAILURE);
	if (x_dup2(pipefd[0], STDIN_FILENO) == DUP2_ERROR)
		exit(EXIT_FAILURE);
	if (x_close(pipefd[0]) == SYS_ERROR)
		exit(EXIT_FAILURE);
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
				read_and_print(STDIN_FILENO);
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

// fd[0]:read, pipefd[1]:write
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
			child_proc(pipefd, pid, cmd);
		else
			parent_proc(pipefd, pid, next_cmd);
		cmd = next_cmd;
	}
	return (EXIT_SUCCESS);
}

// ./a.out "echo" "-e" "aaa\naacc\nbbb\nbbcc\nccc\naabb\nabc" "|" "grep" "a" "|" "grep" "c"