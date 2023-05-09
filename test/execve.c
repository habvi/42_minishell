#include <unistd.h> // execve
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "test.h"

extern char	**environ;

int	main(void)
{
	char	*argv[3];

	argv[0] = "/bin/ls";
	argv[1] = "-l";
	argv[2] = NULL;
	if (execve(argv[0], argv, environ) == EXECVE_ERROR)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
