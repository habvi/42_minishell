#include "ft_dprintf_inter.h"

static void	convert_c_to_str(t_info_pf *info, va_list *args_list)
{
	const char	c = va_arg(*args_list, int);
	char		s_null[1];
	char		s[2];

	if (c == '\0')
	{
		(void)s;
		s_null[0] = c;
		strdup_for_printf(info, s_null);
		return ;
	}
	(void)s_null;
	s[0] = c;
	s[1] = '\0';
	strdup_for_printf(info, s);
}

static void	convert_s_to_str(t_info_pf *info, va_list *args_list)
{
	const char	*s = va_arg(*args_list, char*);

	if (s == NULL)
		s = "(null)";
	strdup_for_printf(info, s);
}

static void	convert_p_to_str(t_info_pf *info, va_list *args_list)
{
	uintptr_t	addr;

	addr = va_arg(*args_list, uintptr_t);
	ptoa_for_printf(addr, info);
}

static void	convert_di_to_str(t_info_pf *info, va_list *args_list)
{
	const int	num = va_arg(*args_list, int);

	if (num < 0)
		info->is_negative_num = true;
	itoa_for_printf(num, info);
}

void	convert_to_str(t_info_pf *info, va_list *args_list)
{
	const char	c = info->type;

	if (c == 'c')
		convert_c_to_str(info, args_list);
	else if (c == 's')
		convert_s_to_str(info, args_list);
	else if (c == 'p')
		convert_p_to_str(info, args_list);
	else if (c == 'd' || c == 'i')
		convert_di_to_str(info, args_list);
	else if (c == 'u')
		convert_u_to_str(info, args_list);
	else if (c == 'x')
		convert_x_to_str(info, args_list);
	else if (c == 'X')
		convert_upperx_to_str(info, args_list);
	else if (c == '%')
		convert_percent_to_str(info);
}
