#include <sys/wait.h>
#include "ft_sys.h"

pid_t	x_wait(int *wstatus)
{
	pid_t	ret;

	errno = 0;
	ret = wait(wstatus);
	if (ret == SYS_ERROR)
		perror("wait");
	return (ret);
}
