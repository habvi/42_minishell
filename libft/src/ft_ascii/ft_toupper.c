#include "ft_ascii.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		c += 'A' - 'a';
	return (c);
}
