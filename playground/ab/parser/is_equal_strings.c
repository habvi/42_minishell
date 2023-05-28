#include <stdbool.h>
#include <stddef.h>

bool	is_equal_strings(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (false);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] || s2[i])
		return (false);
	return (true);
}
