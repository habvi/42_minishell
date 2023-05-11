#include "ft_math.h"

size_t	ft_min(const size_t x, const size_t y)
{
	if (x <= y)
		return (x);
	return (y);
}

double	ft_min_double(const double x, const double y)
{
	if (x <= y)
		return (x);
	return (y);
}
