#include <unistd.h> // fork
#include <sys/wait.h> // wait
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include "test.h"

static void	child_proc(int pipefd[2], pid_t pid)
{
	const char	*s = "abcde\n";

	printf("=== child process start [PID: %d] ===\n", pid);
	close(pipefd[0]);
	close(STDOUT_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	while (*s)
	{
		putchar(*s);
		s++;
	}
	printf("\n=== child process end ===\n\n");
}

static void	parent_proc(int pipefd[2], pid_t pid)
{
	char	c;
	int		status;
	pid_t	wait_pid;

	printf("=== parents process start [PID: %d] ===\n", pid);
	close(pipefd[1]);
	close(STDIN_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	while (true)
	{
		c = getchar();
		if (c == EOF)
			break ;
		putchar(c);
	}
	wait_pid = wait(&status);
	if (wait_pid == WAIT_ERROR)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
	printf("wait pid: %d, status: %d\n", wait_pid, status);
	printf("=== parents process end ===\n\n");
}

// fd[0]:read, pipefd[1]:write
int	main(void)
{
	int		pipefd[2];
	pid_t	pid;

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
		child_proc(pipefd, pid);
	else
		parent_proc(pipefd, pid);
	return (EXIT_SUCCESS);
}
