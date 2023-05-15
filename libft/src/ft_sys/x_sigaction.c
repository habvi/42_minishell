#include <signal.h>
#include "ft_sys.h"

int	x_sigaction(int sig, \
					const struct sigaction *restrict act, \
					struct sigaction *restrict oact)
{
	int	ret;

	errno = 0;
	ret = sigaction(sig, act, oact);
	if (ret == SYS_ERROR)
		perror("sigaction");
	return (ret);
}
