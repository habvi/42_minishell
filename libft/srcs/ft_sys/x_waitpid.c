#include <sys/wait.h>
#include "ft_sys.h"

pid_t	x_waitpid(pid_t pid, int *wstatus, int options)
{
	pid_t	ret;

	errno = 0;
	ret = waitpid(pid, wstatus, options);
	if (ret == SYS_ERROR)
		perror("waitpid");
	return (ret);
}
