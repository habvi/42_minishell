#include <unistd.h> // fork
#include <sys/wait.h> // wait
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "test.h"

static void	child_proc(int pipefd[2], pid_t pid)
{
	const char	*s = "abcde";

	printf("=== child process start [PID: %d] ===\n", pid);
	close(pipefd[0]);
	write(pipefd[1], s, strlen(s));
	close(pipefd[1]);
	printf("=== child process end ===\n");
}

static void	read_from_new_pipe(int fd)
{
	const size_t	BUF_SIZE = 10;
	char			buf[BUF_SIZE];
	ssize_t			rsize;
	while (true)
	{
		rsize = read(fd, buf, BUF_SIZE);
		if (rsize == READ_ERROR)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		if (rsize <= 0)
			break ;
		printf("[rsize: %zd]\n", rsize);
		buf[rsize] = '\0';
		write(STDOUT_FILENO, "|", 1);
		write(STDOUT_FILENO, buf, rsize);
		write(STDOUT_FILENO, "|", 1);
	}
}

static void	parent_proc(int pipefd[2], pid_t pid)
{
	int		status;
	pid_t	wait_pid;

	printf("=== parents process start [PID: %d] ===\n", pid);
	close(pipefd[1]);
	wait_pid = wait(&status);
	if (wait_pid == WAIT_ERROR)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
	read_from_new_pipe(pipefd[0]);
	close(pipefd[0]);
	printf("\nwait pid: %d, status: %d\n", wait_pid, status);
	printf("=== parents process end ===\n");
}

// fd[0]:read, pipefd[1]:write
int	main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	pid;

	(void)argc;
	(void)argv;
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
