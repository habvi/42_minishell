#include "ft_sys.h"

int	x_dup(int fd)
{
	int	ret;

	errno = 0;
	ret = dup(fd);
	if (ret == SYS_ERROR)
		perror("dup");
	return (ret);
}
