#include "ft_string.h"
#include "ft_math.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	size_t	i;

	len_needle = ft_strlen(needle);
	if (!len_needle)
		return ((char *)haystack);
	// if (haystack == NULL && len == 0)
	// 	return (NULL);
	len = ft_min(len, ft_strlen(haystack));
	i = 0;
	while (i + len_needle <= len)
	{
		if (ft_strncmp(&haystack[i], needle, len_needle) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
