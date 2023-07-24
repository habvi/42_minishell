#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
int	main(void)
{
	char *path = "/home/user42/42tokyo/minishell/playground/ta/chdir/link/";


//	errno = 0;
//	int ret = chdir(path);
//	int tmp = errno;
//
//	printf("cdpath:%s\npwd   :%s\nchdir_ret:%d, err:%d, %s\n", path, getcwd(NULL, 0), ret, tmp,
//		   strerror(tmp));

	DIR		*dirp;
	errno = 0;
	dirp = opendir(path);
	int err = errno;
	printf("path:%s, errno:%d, %s\n",path ,err, strerror(err));

	return (0);
}
