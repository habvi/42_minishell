#include <unistd.h> // fork,sleep
#include <sys/wait.h> // wait
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "test.h"

static void	child_proc(void)
{
	printf("=== child process start [PID: %d]===\n", getpid());
	sleep(1);
	printf("\n=== child process end ===\n\n");
	exit(2);
}

static void	parents_proc(pid_t pid)
{
	int		status;
	pid_t	wait_pid;

	printf("=== parents process start [child PID: %d] ===\n", pid);
	status = 0;
	wait_pid = wait(&status);
	if (wait_pid == WAIT_ERROR)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		printf("wait pid: %d, status: %d\n", wait_pid, WEXITSTATUS(status));
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
		child_proc();
	else
		parents_proc(pid);
	return (EXIT_SUCCESS);
}
