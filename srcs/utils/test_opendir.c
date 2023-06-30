#include <dirent.h>
#include <errno.h>
#include "ft_string.h"

bool	test_opendir(const char *path, int *tmp_err)
{
	DIR	*dirp;

	errno = 0;
	dirp = opendir(path);
	*tmp_err = errno;
	closedir(dirp);
	if (*tmp_err != 0)
		return (false);
	return (true);
}
