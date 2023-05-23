#include "ft_dprintf.h"

// __func__, __LINE__
void	debug_func(const char *func_name, const int line_num)
{
	ft_dprintf(STDERR_FILENO, "(%s: line %d)\n", func_name, line_num);
}

void	debug_2d_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		ft_dprintf(STDERR_FILENO, "%s ", array[i]);
		i++;
	}
	ft_dprintf(STDERR_FILENO, "\n");
}
