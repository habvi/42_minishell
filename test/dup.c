#include <fcntl.h> // open
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "test.h"

int	main(int argc, char *argv[])
{
	char	*path;
	int		fd;

	if (argc <= 1)
		exit(EXIT_FAILURE);
	path = argv[1];
	fd = open(path, O_RDONLY);
	if (fd == OPEN_ERROR)
	{
		perror("open");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (execve("/usr/bin/wc", argv + 1, NULL) == EXECVE_ERROR)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
