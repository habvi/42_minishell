#include "ft_dprintf_inter.h"

bool	is_zero_num(t_info_pf *info)
{
	return (info->len_str <= 1 && info->dup_str[0] == '0');
}

void	convert_u_to_str(t_info_pf *info, va_list *args_list)
{
	const unsigned int	num = va_arg(*args_list, unsigned int);

	utoa_for_printf(num, info);
}

void	convert_x_to_str(t_info_pf *info, va_list *args_list)
{
	const unsigned int	num = va_arg(*args_list, unsigned int);

	xtoa_for_printf(num, info, false);
}

void	convert_upperx_to_str(t_info_pf *info, va_list *args_list)
{
	const unsigned int	num = va_arg(*args_list, unsigned int);

	xtoa_for_printf(num, info, true);
}

void	convert_percent_to_str(t_info_pf *info)
{
	char	s[2];

	s[0] = '%';
	s[1] = '\0';
	strdup_for_printf(info, s);
}
