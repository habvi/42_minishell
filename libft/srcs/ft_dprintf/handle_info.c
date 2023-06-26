#include "ft_dprintf_inter.h"
#include "ft_mem.h"

void	init_info(t_info_pf *info, const char *format)
{
	info->fmt = format;
	info->is_format_specifier = false;
	info->minus = false;
	info->plus = false;
	info->hash = false;
	info->zero = false;
	info->len_zero = 0;
	info->width = 0;
	info->dot = false;
	info->precision = 0;
	info->space = false;
	info->type = '\0';
	info->is_negative_num = false;
	info->dup_str = NULL;
	info->len_str = 0;
	info->len_flagged_str = 0;
	info->field_width = 0;
	info->output = NULL;
	info->index = 0;
	info->error = 0;
	info->total_len = 0;
}

void	clear_fmt_info(t_info_pf *info)
{
	info->minus = false;
	info->plus = false;
	info->hash = false;
	info->zero = false;
	info->len_zero = 0;
	info->width = 0;
	info->dot = false;
	info->precision = 0;
	info->space = false;
	info->type = '\0';
	info->is_negative_num = false;
	info->dup_str = NULL;
	info->len_str = 0;
	info->len_flagged_str = 0;
	info->field_width = 0;
}

void	free_dup_str(t_info_pf *info)
{
	ft_free(&info->dup_str);
}

void	put_output(int fd, t_info_pf *info)
{
	ssize_t	res;

	res = write(fd, info->output, info->index);
	if (res == ERROR_WRITE || info->total_len + res >= INT_MAX)
	{
		ft_free(&info->output);
		info->error = EXIT;
		return ;
	}
	info->total_len += res;
	ft_free(&info->output);
}
