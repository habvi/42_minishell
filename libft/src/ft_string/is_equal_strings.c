#include <stdbool.h>
#include "ft_string.h"

/* Returns bool true if s1 == s2, otherwise false.  */
/* If s1 or s2 is NULL, returns false.              */
bool	is_equal_strings(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (false);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (false);
	if (ft_strncmp(s1, s2, s1_len) == 0)
		return (true);
	return (false);
}
