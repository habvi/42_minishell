#include "ft_sys.h"

int	x_unlink(const char *path)
{
	int	ret;

	errno = 0;
	ret = unlink(path);
	if (ret == SYS_ERROR)
		perror("unlink");
	return (ret);
}
