#include <signal.h>
#include "ft_sys.h"

sig_t	x_signal(int sig, sig_t func)
{
	sig_t	ret;

	errno = 0;
	ret = signal(sig, func);
	if (ret == SIG_ERR)
		perror("signal");
	return (ret);
}
