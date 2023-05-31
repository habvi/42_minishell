#include "ft_ascii.h"

bool	ft_isprint(int c)
{
	return (' ' <= c && c <= '~');
}
