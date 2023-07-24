#include "ft_ascii.h"
#include "ft_lib.h"

bool	str_to_legal_number(const char *str, long *result)
{
	long	value;
	char	*endptr;
	bool	is_strtol_success;

	*result = 0;
	if (!str)
		return (false);
	is_strtol_success = ft_strtol(str, &value, &endptr);
	if (!is_strtol_success)
		return (false);
	while (ft_is_whitespace(*endptr))
		endptr++;
	if (*endptr)
		return (false);
	*result = value;
	return (true);
}
