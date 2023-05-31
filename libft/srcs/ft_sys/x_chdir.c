#include "ft_sys.h"

int	x_chdir(const char *path)
{
	int	ret;

	errno = 0;
	ret = chdir(path);
	if (ret == SYS_ERROR)
		perror("chdir");
	return (ret);
}
