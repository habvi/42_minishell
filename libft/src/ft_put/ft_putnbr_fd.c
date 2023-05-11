#include "ft_put.h"
#include <limits.h>

void	ft_putnbr_fd(int n, int fd)
{
	size_t	num;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == INT_MIN)
			num = (size_t)(-(n + 1)) + 1;
		else
			num = -n;
	}
	else
		num = n;
	if (num < 10)
	{
		ft_putchar_fd(num + '0', fd);
		return ;
	}
	ft_putnbr_fd(num / 10, fd);
	ft_putnbr_fd(num % 10, fd);
}
