#include "ft_sys.h"

int	x_close(int fd)
{
	int	ret;

	errno = 0;
	ret = close(fd);
	if (ret == SYS_ERROR)
		perror("close");
	return (ret);
}
