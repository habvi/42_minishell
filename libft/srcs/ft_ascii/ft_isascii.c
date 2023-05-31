#include "ft_ascii.h"

bool	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}
