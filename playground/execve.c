#include <unistd.h> // execve
#include <unistd.h> // fork
#include <sys/wait.h> // wait
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "test.h"

extern char	**environ;

static void	child_proc(char *argv[])
{
	const char	*path = argv[1];

	printf("=== child process start [PID: %d]===\n", getpid());
	if (execve(path, argv + 1, environ) == EXECVE_ERROR)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
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

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc == 1)
		return (EXIT_SUCCESS);
	pid = fork();
	if (pid == FORK_ERROR)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == CHILD_PID)
		child_proc(argv);
	else
		parents_proc(pid);
	return (EXIT_SUCCESS);
}
