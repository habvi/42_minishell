#include <sys/wait.h>
#include "ft_sys.h"

pid_t	x_wait(int *stat_loc)
{
	pid_t	ret;

	errno = 0;
	ret = wait(stat_loc);
	if (ret == SYS_ERROR)
		perror("wait");
	return (ret);
}
