#include <stdint.h>
#include "ft_lib.h"
#include "ft_sys.h"

static void	set_digit_and_power(int n, uint8_t *digit, unsigned int *power)
{
	(*digit)++;
	if (-10 < n && n < 10)
	{
		if (n < 0)
			(*digit)++;
		return ;
	}
	*power *= 10;
	set_digit_and_power(n / 10, digit, power);
}

static char	*set_to_list(int n, uint8_t digit, unsigned int power)
{
	char	*res;
	size_t	i;

	res = (char *)x_malloc(sizeof(char) * (digit + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		res[0] = '-';
		i++;
	}
	while (i < digit)
	{
		if (n < 0)
			res[i] = -(n / (int)power % 10) + '0';
		else
			res[i] = n / (int)power % 10 + '0';
		power /= 10;
		i++;
	}
	res[digit] = '\0';
	return (res);
}

char	*ft_itoa_int(int n)
{
	uint8_t			digit;
	unsigned int	power;

	power = 1;
	if (n == 0)
		digit = 1;
	else
	{
		digit = 0;
		set_digit_and_power(n, &digit, &power);
	}
	return (set_to_list(n, digit, power));
}

// #include <stdio.h>

// int main()
// {
// 	printf("%s\n", ft_itoa(2147483647));
// 	printf("%s\n", ft_itoa(12345));
// 	printf("%s\n", ft_itoa(10));
// 	printf("%s\n", ft_itoa(6));
// 	printf("%s\n", ft_itoa(0));
// 	printf("%s\n", ft_itoa(-9));
// 	printf("%s\n", ft_itoa(-12345));
// 	printf("%s\n", ft_itoa(-2147483648));
// }
