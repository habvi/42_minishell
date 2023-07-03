#include <stdlib.h>
#include "ms_builtin.h"
#include "ms_var.h"

// -x -> attr=VAR_ENV
// +x -> attr=VAR_SHELL
static t_var_attr	get_declare_attr_from_arg(const char *const *argv, \
													size_t *i)
{
	if (is_arg_option(argv[*i], CMD_OPTION_MARKER, DECLARE_OPTION_VAR_ENV))
	{
		(*i)++;
		return (VAR_ENV);
	}
	if (is_arg_option(argv[*i], \
					DECLARE_DEL_ATTR_MARKER, \
					DECLARE_OPTION_VAR_ENV))
	{
		(*i)++;
		return (VAR_SHELL);
	}
	return (VAR_NONE);
}

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
	is_display_attr = skip_valid_options(argv, \
										&i, \
										CMD_OPTION_MARKER, \
										DECLARE_OPTION_DISPLAY_ATTR);
	if (is_end_of_option(argv[i]))
		i++;
	if (!argv[i])
	{
		var->print_detail(var, var_all, is_display_attr);
		return (status);
	}
	attr = get_declare_attr_from_arg(argv, &i);
	var_declare_all(&argv[i], var, &status, attr);
	return (status);
}
