#include "ft_ascii.h"

static bool	ft_islower(int c)
{
	return ('a' <= c && c <= 'z');
}

static bool	ft_isupper(int c)
{
	return ('A' <= c && c <= 'Z');
}

bool	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
