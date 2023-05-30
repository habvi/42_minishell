#include "ft_sys.h"

ssize_t	x_write(int fd, const void *buf, size_t nbyte)
{
	ssize_t	ret;

	errno = 0;
	ret = write(fd, buf, nbyte);
	if (ret == SYS_ERROR)
		perror("write");
	return (ret);
}
