#include <stdbool.h>
#include "ft_string.h"

/* Returns bool true if s1 == s2, otherwise false.  */
/* If s1 or s2 is NULL, returns false.              */
bool	ft_streq(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (true);
	if (!s1 || !s2)
		return (false);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] || s2[i])
		return (false);
	return (true);
}
