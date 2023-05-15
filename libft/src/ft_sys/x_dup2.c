#include "ft_sys.h"

int	x_dup2(int fd, int fd2)
{
	int	ret;

	errno = 0;
	ret = dup2(fd, fd2);
	if (ret == SYS_ERROR)
		perror("dup2");
	return (ret);
}
