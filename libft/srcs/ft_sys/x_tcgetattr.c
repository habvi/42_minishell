#include "ft_sys.h"

int	x_tcgetattr(int fd, struct termios *termios_p)
{
	int	ret;

	errno = 0;
	ret = tcgetattr(fd, termios_p);
	if (ret == SYS_ERROR)
		perror("tcgetattr");
	return (ret);
}
