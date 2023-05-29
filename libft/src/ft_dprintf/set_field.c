#include "ft_dprintf_inter.h"
#include "libft.h"

static void	set_for_mandatory(t_info_pf *info)
{
	info->field_width = info->len_str + info->is_negative_num;
}

static bool	is_csp2_types(t_info_pf *info)
{
	return (info->type == 'c' || info->type == 's' || \
			info->type == 'p' || info->type == '%');
}

static void	set_field_width_csp2(t_info_pf *info)
{
	if (info->type == 'c')
		info->field_width = ft_max(1, info->width);
	else
	{
		if (info->type == 's')
		{
			if (info->dot && info->precision < info->len_str)
				info->len_str = info->precision;
		}
		else if (info->type == '%')
		{
			info->precision = 0;
			info->space = false;
		}
		info->field_width = ft_max(info->width, info->len_str);
	}
	info->len_flagged_str = info->len_str;
}

static void	set_field_width_diux2(t_info_pf *info)
{
	size_t	add_flag;

	if (info->type == 'x' || info->type == 'X')
	{
		if (info->hash && !is_zero_num(info))
			add_flag = 2;
		else
			add_flag = 0;
	}
	else
	{
		if (info->plus || info->is_negative_num || info->space)
			add_flag = 1;
		else
			add_flag = 0;
	}
	if (info->dot && !info->precision && is_zero_num(info))
		info->len_str = 0;
	info->len_flagged_str = info->len_str + add_flag;
	info->field_width = ft_max(info->width, info->len_flagged_str);
	if (info->precision > info->len_str)
	{
		info->field_width = ft_max(info->field_width, \
							ft_max(info->precision, info->len_str) + add_flag);
	}
}

void	set_field_width(t_info_pf *info)
{
	if (info->type && *(info->fmt - 2) == '%')
	{
		set_for_mandatory(info);
		return ;
	}
	if (is_csp2_types(info))
		set_field_width_csp2(info);
	else
		set_field_width_diux2(info);
}
