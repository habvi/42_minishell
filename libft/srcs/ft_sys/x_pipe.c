#include "ft_sys.h"

int	x_pipe(int pipe_fd[2])
{
	int	ret;

	errno = 0;
	ret = pipe(pipe_fd);
	if (ret == SYS_ERROR)
		perror("pipe");
	return (ret);
}
