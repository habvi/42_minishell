#ifndef FT_DPRINTF_INTER_H
# define FT_DPRINTF_INTER_H

# include <stdarg.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>

# include "ft_dprintf.h"

# define FORMAT_TYPES		"cspdiuxX%"
# define HEX				"0123456789abcdef"
# define WIDTH				1
# define PRECISION			2

# define ERROR_MALLOC		1
# define ERROR_OVERFLOW		2
# define ERROR_WRITE		-1
# define ERROR_FT_DPRINTF	-1
# define EXIT				3

typedef struct s_info_pf
{
	const char	*fmt;
	bool		is_format_specifier;
	bool		minus;
	bool		plus;
	bool		hash;
	bool		zero;
	size_t		len_zero;
	size_t		width;
	bool		dot;
	size_t		precision;
	bool		space;
	char		type;
	bool		is_negative_num;
	char		*dup_str;
	size_t		len_str;
	size_t		len_flagged_str;
	size_t		field_width;
	char		*output;
	size_t		index;
	size_t		error;
	size_t		total_len;
}	t_info_pf;

// handle_info.c
void	init_info(t_info_pf *info, const char *format);
void	clear_fmt_info(t_info_pf *info);
void	free_dup_str(t_info_pf *info);
void	put_output(int fd, t_info_pf *info);

// parse_format.c
void	set_format_flags(t_info_pf *info);
void	check_ignored_flags(t_info_pf *info);

// convert_to_str.c
void	convert_to_str(t_info_pf *info, va_list *args_list);
// convert_to_str2.c
bool	is_zero_num(t_info_pf *info);
void	convert_u_to_str(t_info_pf *info, va_list *args_list);
void	convert_x_to_str(t_info_pf *info, va_list *args_list);
void	convert_upperx_to_str(t_info_pf *info, va_list *args_list);
void	convert_percent_to_str(t_info_pf *info);

// strdup_for_printf.c
void	strdup_for_printf(t_info_pf *info, const char *src);

// itoa_utoa_for_printf.c
void	itoa_for_printf(int n, t_info_pf *info);
void	utoa_for_printf(unsigned int n, t_info_pf *info);
// ptoa_xtoa_for_printf.c
void	ptoa_for_printf(uintptr_t n, t_info_pf *info);
void	xtoa_for_printf(unsigned int n, t_info_pf *info, bool is_upper);

// set_field.c
void	set_field_width(t_info_pf *info);

// set_output.c
void	set_output(t_info_pf *info);

#endif
