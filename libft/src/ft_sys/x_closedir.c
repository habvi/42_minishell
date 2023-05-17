#include "ft_sys.h"

int	x_closedir(DIR *dirp)
{
	int	ret;

	errno = 0;
	ret = closedir(dirp);
	if (ret == SYS_ERROR)
		perror("closedir");
	return (ret);
}
