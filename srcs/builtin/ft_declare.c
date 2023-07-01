#include <stdlib.h>
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_string.h"

// -x -> attr=VAR_ENV
// +x -> attr=VAR_SHELL
static t_var_attr	get_declare_attr(const char *const *argv, size_t *i)
{
	if (ft_streq(argv[*i], "-x")) // can't handle now, not discriminate op
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

// now     : arg is 'key'
// feature : arg is key=value or key+=value... etc
//            -> call declare_all or var_declare_arg
static void	change_arg_attr(t_var *var, const char *key, t_var_attr attr)
{
	var->update_attr(var, key, attr);
}

// option : -p    display the attributes and value of each NAME
// `+x' instead of `-x' turns off the given attribute.
// Now, "only -p" or "only one arg" can declare, such as following:
//   $ declare -p
//   $ declare -x key
//   $ declare +x key
// feature:
//   $ declare -p +x/-x key=value key+=value ...
uint8_t	ft_declare(const char *const *argv, t_var *var)
{
	uint8_t		status;
	size_t		i;
	bool		is_display_attr;
	t_var_attr	attr;

	status = EXIT_SUCCESS;
	i = 1;
	skip_option_part(argv, &i, &is_display_attr, DECLARE_OPTION_DISPLAY_ATTR);
	if (!argv[i])
	{
		var->print_detail(var, VAR_ALL, is_display_attr);
		return (status);
	}
	attr = get_declare_attr(argv, &i);
	change_arg_attr(var, argv[i], attr); // arg must 'key'
	return (status);
}
