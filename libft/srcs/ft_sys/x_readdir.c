#include "ft_sys.h"

struct dirent	*x_readdir(DIR *dirp)
{
	struct dirent	*ret;

	errno = 0;
	ret = readdir(dirp);
	if (!ret)
		perror("readdir");
	return (ret);
}
