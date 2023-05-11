#include "ft_lib.h"
#include "ft_ascii.h"
#include <limits.h>

static bool	is_leading_zeros(const char *head, const char *str, int num)
{
	if (num != 0)
		return (false);
	if (head == str)
		return (false);
	if (*str != '0')
		return (false);
	return (true);
}

static bool	is_overflow(int *num, int c)
{
	int	max_div;
	int	max_mod;

	max_div = INT_MAX / 10;
	max_mod = INT_MAX % 10;
	if (*num > max_div)
	{
		*num = 0;
		return (true);
	}
	if (*num == max_div && c - '0' > max_mod)
	{
		*num = 0;
		return (true);
	}
	return (false);
}

bool	ft_atoi_strictly(const char *str, int *num)
{
	const char	*head = str;
	bool		at_least_one_digit;

	*num = 0;
	at_least_one_digit = false;
	while (ft_isdigit(*str))
	{
		at_least_one_digit = true;
		if (is_leading_zeros(head, str, *num))
			return (false);
		if (is_overflow(num, *str))
			return (false);
		*num = *num * 10 + *str - '0';
		str++;
	}
	if (*str || !at_least_one_digit)
		return (false);
	return (true);
}

/*
#include <stdbool.h>
#include <assert.h>

int	main(void)
{
	int	num;

	assert(ft_atoi_strictly("-", &num) == false);
	assert(ft_atoi_strictly("+", &num) == false);
	assert(ft_atoi_strictly("a", &num) == false);
	assert(ft_atoi_strictly("a1", &num) == false);
	assert(ft_atoi_strictly("1   ", &num) == false);
	assert(ft_atoi_strictly("1a", &num) == false);
	assert(ft_atoi_strictly("   1", &num) == false);
	assert(ft_atoi_strictly("+0", &num) == false);
	assert(ft_atoi_strictly("+1", &num) == false);
	assert(ft_atoi_strictly("+001", &num) == false);
	assert(ft_atoi_strictly("-1", &num) == false);
	assert(ft_atoi_strictly("2147483648", &num) == false);
	assert(ft_atoi_strictly("000", &num) == false);
	assert(ft_atoi_strictly("0011", &num) == false);

	assert(ft_atoi_strictly("0", &num) == true);
	assert(ft_atoi_strictly("11", &num) == true);
	assert(ft_atoi_strictly("2147483647", &num) == true);
}
*/
