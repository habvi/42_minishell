#include "ft_sys.h"

int	x_open(int fd, const char *path, int oflag)
{
	int	ret;

	errno = 0;
	ret = open(fd, path, oflag);
	if (ret == SYS_ERROR)
		perror("open");
	return (ret);
}
