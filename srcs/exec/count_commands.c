#include <unistd.h>

size_t	count_commands(char *const *commands)
{
	size_t	i;

	i = 0;
	while (commands[i])
		i++;
	return (i);
}
