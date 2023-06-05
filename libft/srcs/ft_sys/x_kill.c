#include <signal.h>
#include "ft_sys.h"

int	x_kill(pid_t pid, int sig)
{
	int	ret;

	errno = 0;
	ret = kill(pid, sig);
	if (ret == SYS_ERROR)
		perror("kill");
	return (ret);
}
