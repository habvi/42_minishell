#include "ft_sys.h"

char	*x_ttyname(int fd)
{
	char	*ret;

	errno = 0;
	ret = ttyname(fd);
	if (!ret)
		perror("ttyname");
	return (ret);
}
