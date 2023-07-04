#include "ft_string.h"

char	*ft_find_set_in_str(char *str, const char *set)
{
	while (*str && !ft_strchr(set, *str))
		str++;
	return (str);
}
