#include "ft_sys.h"

int	x_isatty(int fd)
{
	int	ret;

	errno = 0;
	ret = isatty(fd);
	if (ret == TTY_ERROR)
		perror("isatty");
	return (ret);
}
