#include "ft_sys.h"

int	x_tcsetattr(int fd, int optional_actions, const struct termios *termios_p)
{
	int	ret;

	errno = 0;
	ret = tcsetattr(fd, optional_actions, termios_p);
	if (ret == SYS_ERROR)
		perror("tcsetattr");
	return (ret);
}
