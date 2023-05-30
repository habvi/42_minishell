#include <stdbool.h>
#include "ms_builtin.h"
#include "ft_lib.h"

static bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

bool	ft_legal_number(const char *str, long *result)
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
	while (is_whitespace(*endptr))
		endptr++;
	if (*endptr)
		return (false);
	*result = value;
	return (true);
}
