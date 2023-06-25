#include "ft_dprintf_inter.h"
#include "ft_string.h"
#include "ft_sys.h"

static void	parse_format(t_info_pf *info, va_list *args_list)
{
	info->fmt++;
	while (*info->fmt && ft_strchr(FORMAT_TYPES, *info->fmt) == NULL)
	{
		set_format_flags(info);
		if (info->error)
			return ;
	}
	check_ignored_flags(info);
	info->type = *info->fmt;
	convert_to_str(info, args_list);
	if (info->error)
		return ;
	info->fmt++;
	set_field_width(info);
	info->output = (char *)x_malloc(sizeof(char) * (info->field_width + 1));
	if (info->output == NULL)
	{
		info->error = ERROR_MALLOC;
		free_dup_str(info);
		return ;
	}
	set_output(info);
}

static void	format_specifier_mode(int fd, t_info_pf *info, va_list *args_list)
{
	parse_format(info, args_list);
	if (info->error)
		return ;
	info->is_format_specifier = false;
	put_output(fd, info);
}

static void	normal_char_mode(int fd, t_info_pf *info)
{
	while (*info->fmt && *info->fmt != '%')
	{
		if (write(fd, info->fmt, 1) == ERROR_WRITE || \
			info->total_len == INT_MAX)
		{
			info->error = EXIT;
			return ;
		}
		info->total_len++;
		info->fmt++;
	}
	info->is_format_specifier = true;
	if (!info->fmt)
		info->fmt++;
}

static void	format_specifier_or_not(int fd, t_info_pf *info, va_list *args_list)
{
	while (*info->fmt)
	{
		if (info->is_format_specifier)
		{
			format_specifier_mode(fd, info, args_list);
			clear_fmt_info(info);
		}
		else
			normal_char_mode(fd, info);
		if (info->error)
			return ;
	}
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_info_pf	info;
	va_list		args_list;

	if (fd < 0 || format == NULL)
		return (ERROR_FT_DPRINTF);
	va_start(args_list, format);
	init_info(&info, format);
	format_specifier_or_not(fd, &info, &args_list);
	va_end(args_list);
	if (info.error)
		return (ERROR_FT_DPRINTF);
	return (info.total_len);
}
