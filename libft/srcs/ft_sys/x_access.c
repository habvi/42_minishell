#include "ft_sys.h"

int	x_access(const char *path, int mode)
{
	int	ret;

	errno = 0;
	ret = access(path, mode);
	if (ret == SYS_ERROR)
		perror("access");
	return (ret);
}
