#include "ft_sys.h"

int	x_pipe(int fd[2])
{
	int	ret;

	errno = 0;
	ret = pipe(fd);
	if (ret == SYS_ERROR)
		perror("pipe");
	return (ret);
}
