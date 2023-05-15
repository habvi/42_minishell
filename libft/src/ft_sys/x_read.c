#include "ft_sys.h"

ssize_t	x_read(int fd, void *buf, size_t nbyte)
{
	ssize_t	ret;

	errno = 0;
	ret = read(fd, buf, nbyte);
	if (ret == SYS_ERROR)
		perror("read");
	return (ret);
}
