#include "ft_sys.h"

int	x_execve(const char *path, char *const argv[], char *const envp[])
{
	int	ret;

	errno = 0;
	ret = execve(path, argv, envp);
	if (ret == SYS_ERROR)
		perror("execve");
	return (ret);
}
