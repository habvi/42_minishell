#include <stdlib.h>
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_string.h"

// -x -> attr=VAR_ENV
// +x -> attr=VAR_SHELL
// todo: bit arithmetic ... ?
static t_var_attr	get_declare_attr_from_option(const char *const *argv, \
													size_t *i)
{
	if (ft_streq(argv[*i], "-x"))
	{
		(*i)++;
		return (VAR_ENV);
	}
	if (ft_streq(argv[*i], "+x"))
	{
		(*i)++;
		return (VAR_SHELL);
	}
	return (VAR_NONE);
}

//static void	change_arg_attr(t_var *var, const char *key, t_var_attr attr)
//{
//	var->update_attr(var, key, attr);
//}

// option : -p    display the attributes and value of each NAME
uint8_t	ft_declare(const char *const *argv, t_var *var)
{
	const int	var_all = VAR_ENV | VAR_SHELL;
	uint8_t		status;
	size_t		i;
	bool		is_display_attr;
	t_var_attr	attr;

	status = EXIT_SUCCESS;
	i = 1;
	skip_option_part(argv, &i, &is_display_attr, DECLARE_OPTION_DISPLAY_ATTR);
	if (!argv[i])
	{
		var->print_detail(var, var_all, is_display_attr);
		return (status);
	}
	attr = get_declare_attr_from_option(argv, &i);
	declare_all(&argv[i], var, &status, attr);
//	change_arg_attr(var, argv[i], attr); // <- included in declare_all
	return (status);
}
