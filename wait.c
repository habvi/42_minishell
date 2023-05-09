#include <unistd.h> // fork,sleep
#include <sys/wait.h> // wait
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "test.h"

static void	child_proc(pid_t pid)
{
	printf("=== child process start [PID: %d]===\n", pid);
	sleep(2);
	printf("\n=== child process end ===\n\n");
}

static void	parents_proc(pid_t pid)
{
	int		status;
	pid_t	wait_pid;

	printf("=== parents process start [PID: %d] ===\n", pid);
	status = 0;
	wait_pid = wait(&status);
	if (wait_pid == WAIT_ERROR)
	{
		perror("wait error");
		exit(EXIT_FAILURE);
	}
	printf("wait pid: %d, status: %d\n", wait_pid, status);
	printf("=== parents process end ===\n\n");
}

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == FORK_ERROR)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == CHILD_PID)
	{
		child_proc(pid);
		return (EXIT_SUCCESS);
	}
	parents_proc(pid);
	return (EXIT_SUCCESS);
}
