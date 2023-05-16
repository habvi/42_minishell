#include <unistd.h> // fork
#include <sys/wait.h> // wait
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "test.h"

extern char	**environ;

static void	child_proc(int pipefd[2], pid_t pid, char *argv[])
{
	printf("=== child process start [PID: %d] ===\n", pid);
	close(pipefd[0]);
	close(STDOUT_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	if (execve(argv[1], argv + 1, environ) == EXECVE_ERROR)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	printf("=== child process end ===\n");
}

static void	read_from_pipe_and_exec(int fd)
{
	const size_t	BUF_SIZE = 10;
	char			buf[BUF_SIZE];
	ssize_t			rsize;

	printf("=== parent process read ===\n");
	const char *commands[] = {"/bin/cat", NULL};
	if (execve(commands[0], commands, environ) == EXECVE_ERROR)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

static void	parent_proc(int pipefd[2], pid_t pid)
{
	int		status;
	pid_t	wait_pid;

	printf("=== parents process start [PID: %d] ===\n", pid);
	close(pipefd[1]);
	close(STDIN_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	wait_pid = wait(&status);
	if (wait_pid == WAIT_ERROR)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
	read_from_pipe_and_exec(STDIN_FILENO);
	if (WIFEXITED(status))
		printf("\nwait pid: %d, status: %d\n", wait_pid, WEXITSTATUS(status));
	printf("=== parents process end ===\n");
}

// fd[0]:read, pipefd[1]:write
int	main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	pid;

	(void)argc;
	if (pipe(pipefd) == PIPE_ERROR)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	printf("fd[0] : %d, fd[1]: %d\n", pipefd[0], pipefd[1]);
	pid = fork();
	if (pid == FORK_ERROR)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == CHILD_PID)
		child_proc(pipefd, pid, argv);
	else
		parent_proc(pipefd, pid);
	return (EXIT_SUCCESS);
}
