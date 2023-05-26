#include <fcntl.h> // open
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "test.h"

// file: aaabbb
static void	write_both(const char *file)
{
	const int	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);

	if (fd == OPEN_ERROR)
	{
		perror("open");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	write(fd, "aaa", 3);
	write(STDOUT_FILENO, "bbb", 3);
}

// ./a.out /bin/echo -e ccc
// file: bbbccc
static void	write_only_stdout(const char *file, char *argv[])
{
	const int	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);

	if (fd == OPEN_ERROR)
	{
		perror("open");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	write(fd, "aaa", 3); // -1
	write(STDOUT_FILENO, "bbb", 3);
	if (execve(argv[0], argv + 1, NULL) == EXECVE_ERROR)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	write_both("out1.txt");
	if (argc == 1)
		exit(EXIT_FAILURE);
	write_only_stdout("out2.txt", argv);
}
