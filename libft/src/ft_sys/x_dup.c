#include "ft_sys.h"

int	x_dup(int oldfd)
{
	int	ret;

	errno = 0;
	ret = dup(oldfd);
	if (ret == SYS_ERROR)
		perror("dup");
	return (ret);
}
