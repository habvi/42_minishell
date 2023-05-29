#include "ft_sys.h"

char	*x_getcwd(char *buf, size_t size)
{
	char	*ret;

	errno = 0;
	ret = getcwd(buf, size);
	if (!ret)
		perror("getcwd");
	return (ret);
}
