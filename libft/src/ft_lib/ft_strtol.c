#include <limits.h>
#include "ft_lib.h"
#include "ft_ascii.h"

static bool	is_space(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ');
}

static void	get_sign(const char *str, size_t *idx, int *sign)
{
	*sign = 1;
	if (str[*idx] != '+' && str[*idx] != '-')
		return ;
	if (str[*idx] == '+')
	{
		*idx += 1;
		return ;
	}
	if (str[*idx] == '-')
	{
		*idx += 1;
		*sign = -1;
	}
}

static bool	is_overflow(long before_x10_val, int add_val, int sign)
{
	long	ov_div;
	long	ov_mod;

	if (sign == 1)
	{
		ov_div = LONG_MAX / 10;
		ov_mod = LONG_MAX % 10;
	}
	else
	{
		ov_div = -(LONG_MIN / 10);
		ov_mod = -(LONG_MIN % 10);
	}
	if (before_x10_val > ov_div)
		return (true);
	if (before_x10_val == ov_div && add_val > ov_mod)
		return (true);
	return (false);
}

static long	get_long_num(const char *str, size_t *idx, int sign, bool *is_of)
{
	long	ret_num;
	int		digit;

	ret_num = 0;
	*is_of = false;
	while (ft_isdigit(str[*idx]))
	{
		digit = str[*idx] - '0';
		if (is_overflow(ret_num, digit, sign))
		{
			*is_of = true;
			while (ft_isdigit(str[*idx]))
				*idx += 1;
			if (sign == 1)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		ret_num = ret_num * 10 + digit;
		*idx += 1;
	}
	ret_num *= sign;
	return (ret_num);
}

bool	ft_strtol(const char *str, long *ret_num, char **endptr)
{
	int		sign;
	size_t	idx;
	bool	is_overflow_occurred;

	*ret_num = 0;
	idx = 0;
	if (endptr)
		*endptr = (char *)&str[idx];
	while (is_space(str[idx]))
		idx++;
	get_sign(str, &idx, &sign);
	if (!ft_isdigit(str[idx]))
		return (false);
	*ret_num = get_long_num(str, &idx, sign, &is_overflow_occurred);
	if (endptr)
		*endptr = (char *)&str[idx];
	if (str[idx])
		return (false);
	if (is_overflow_occurred)
		return (false);
	return (true);
}
