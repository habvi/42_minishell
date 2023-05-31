#include "ft_sys.h"

pid_t	x_fork(void)
{
	pid_t	ret;

	errno = 0;
	ret = fork();
	if (ret == SYS_ERROR)
		perror("fork");
	return (ret);
}
