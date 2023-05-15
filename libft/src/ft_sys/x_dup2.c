#include "ft_sys.h"

int	x_dup2(int oldfd, int newfd)
{
	int	ret;

	errno = 0;
	ret = dup2(oldfd, newfd);
	if (ret == SYS_ERROR)
		perror("dup2");
	return (ret);
}
