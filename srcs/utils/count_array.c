#include <unistd.h>

static size_t	count_array_elem(const char *const *array)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

size_t	count_argv(const char *const *argv)
{
	return (count_array_elem(argv));
}
