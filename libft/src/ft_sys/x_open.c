#include <fcntl.h>
#include "ft_sys.h"

int	x_open(const char *path, int oflag)
{
	int	ret;

	errno = 0;
	ret = open(path, oflag);
	if (ret == SYS_ERROR)
		perror("open");
	return (ret);
}
