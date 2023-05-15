#include "ft_sys.h"

void	*x_malloc(size_t size)
{
	void	*ret;

	errno = 0;
	ret = malloc(size);
	if (!ret)
	{
		perror("malloc");
		return (NULL);
	}
	return (ret);
}
