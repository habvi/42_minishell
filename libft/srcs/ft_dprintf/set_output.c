#include "ft_dprintf_inter.h"

static void	fill_n_with_c(t_info_pf *info, size_t size, char c)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		info->output[info->index] = c;
		info->index++;
		i++;
	}
}

static void	copy_str(t_info_pf *info, bool is_bonus)
{
	size_t	i;

	if (!is_bonus && info->is_negative_num)
		fill_n_with_c(info, 1, '-');
	i = 0;
	while (i < info->len_str)
	{
		info->output[info->index] = info->dup_str[i];
		info->index++;
		i++;
	}
	info->output[info->index] = '\0';
	free_dup_str(info);
}

static void	set_sign_0x_space(t_info_pf *info)
{
	if (info->is_negative_num)
		fill_n_with_c(info, 1, '-');
	else if (info->plus && (info->type == 'd' || info->type == 'i'))
		fill_n_with_c(info, 1, '+');
	else if (info->hash && (info->type == 'x' || info->type == 'X') \
		&& !is_zero_num(info))
	{
		fill_n_with_c(info, 1, '0');
		fill_n_with_c(info, 1, info->type);
	}
	else if (info->space && info->type != 's')
		fill_n_with_c(info, 1, ' ');
}

static void	calc_len_zero(t_info_pf *info)
{
	info->len_zero = 0;
	if (!info->precision)
	{
		if (info->zero && info->width > info->len_flagged_str)
			info->len_zero = info->width - info->len_flagged_str;
	}
	else
	{
		if (info->len_str && info->precision > info->len_str)
			info->len_zero = info->precision - info->len_str;
	}
	if (info->type == 's')
		info->len_zero = 0;
}

void	set_output(t_info_pf *info)
{
	size_t	len_space;

	info->index = 0;
	if (info->type && *(info->fmt - 2) == '%')
	{
		copy_str(info, false);
		return ;
	}
	calc_len_zero(info);
	len_space = info->field_width - info->len_flagged_str - info->len_zero;
	if (!info->minus)
		fill_n_with_c(info, len_space, ' ');
	set_sign_0x_space(info);
	fill_n_with_c(info, info->len_zero, '0');
	copy_str(info, true);
	if (info->minus)
		fill_n_with_c(info, len_space, ' ');
}
