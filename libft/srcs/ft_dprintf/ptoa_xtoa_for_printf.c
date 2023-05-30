#include "ft_dprintf_inter.h"
#include "libft.h"

static size_t	count_length(size_t num, size_t now)
{
	if (!num)
		return (now);
	return (count_length(num / 16, now + 1));
}

static char	*set_to_list_for_p(size_t num, size_t start, size_t len)
{
	char	*res;
	size_t	i;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (start + i < len)
	{
		res[len - i - 1] = HEX[num % 16];
		num /= 16;
		i++;
	}
	res[len] = '\0';
	return (res);
}

void	ptoa_for_printf(uintptr_t n, t_info_pf *info)
{
	size_t	num;
	size_t	len;

	num = n;
	len = count_length(num, 0) + 2;
	if (n == 0)
		len++;
	info->dup_str = set_to_list_for_p(num, 2, len);
	if (info->dup_str == NULL)
	{
		info->error = ERROR_MALLOC;
		return ;
	}
	info->dup_str[0] = '0';
	info->dup_str[1] = 'x';
	info->len_str = len;
}

static char	*set_to_list_for_x(size_t num, size_t len, bool is_upper)
{
	char	*res;
	size_t	i;
	char	hex;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		hex = HEX[num % 16];
		if (is_upper)
			hex = ft_toupper(hex);
		res[len - i - 1] = hex;
		num /= 16;
		i++;
	}
	res[len] = '\0';
	return (res);
}

void	xtoa_for_printf(unsigned int n, t_info_pf *info, bool is_upper)
{
	size_t	num;
	size_t	len;

	num = n;
	len = count_length(num, 0) + (n == 0);
	info->dup_str = set_to_list_for_x(num, len, is_upper);
	if (info->dup_str == NULL)
		info->error = ERROR_MALLOC;
	info->len_str = len;
}
