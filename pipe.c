#include <unistd.h> // fork,sleep
#include <sys/wait.h> // wait
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h> // toupper
#include "test.h"

static void	child_proc(int pipefd[2], pid_t pid)
{
	char	c;
	char	c2;
	ssize_t	read_size;

	printf("=== child process start [PID: %d] ===\n", pid);
	close(pipefd[1]);
	while (true)
	{
		read_size = read(pipefd[0], &c, 1);
		if (read_size == READ_ERROR)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		if (!read_size)
			break ;
		c2 = toupper(c);
		if (write(STDOUT_FILENO, &c2, 1) == WRITE_ERROR)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
	}
	close(pipefd[0]);
	printf("\n=== child process end ===\n\n");
}

static void	parent_proc(int pipefd[2], pid_t pid)
{
	char	*s = "abcde\n";
	int		status;
	pid_t	wait_pid;

	printf("=== parents process start [PID: %d] ===\n", pid);
	close(pipefd[0]);
	while (*s)
	{
		if (write(pipefd[1], s, 1) == WRITE_ERROR)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		s++;
	}
	close(pipefd[1]);
	status = 0;
	wait_pid = wait(&status);
	if (wait_pid == WAIT_ERROR)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
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
	{
		child_proc(pipefd, pid);
		exit(EXIT_SUCCESS);
	}
	parent_proc(pipefd, pid);
	return (EXIT_SUCCESS);
}
