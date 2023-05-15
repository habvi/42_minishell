#include "ft_sys.h"

DIR	*x_opendir(const char *filename)
{
	DIR	*ret;

	errno = 0;
	ret = opendir(filename);
	if (!ret)
		perror("opendir");
	return (ret);
}
