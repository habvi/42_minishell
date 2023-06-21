#include <unistd.h>

static size_t	count_array_elem(char *const *array)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

size_t	count_commands(char *const *commands)
{
	return (count_array_elem(commands));
}

size_t	count_argc(char *const *argc)
{
	return (count_array_elem(argc));
}
