#include <unistd.h> // fork
#include <sys/types.h> // pid_t
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "test.h"

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
		printf("child!!!\n");
	else
		printf("parent!!!\n");
	return (EXIT_SUCCESS);
}