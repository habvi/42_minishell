#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_string.h"

// "~"  -> HOME
// "-"  -> OLDPWD
// else -> arg
static char	*set_path_by_arg(const char *arg, t_var *var, bool *is_print_path)
{
	char	*path;

	if (ft_streq(arg, CD_ARG_HOME)) // ~ todo: expansion
		path = var->get_value(var, KEY_HOME);
	else if (ft_streq(arg, CD_ARG_OLDPWD)) // -
	{
		*is_print_path = true;
		path = var->get_value(var, KEY_OLDPWD);
	}
	else if (ft_streq(arg, ""))
		path = x_ft_strdup(PATH_CURRENT);
	else
		path = search_cdpath(arg, var, is_print_path);
	return (path);
}

//  arg                       bash                         minishell
// unset HOME; cd <no arg>   path=NULL; HOME not set
// unset HOME; cd ~          getpath from /etc/passwd   (tmp) same as <no arg>
// -> unset OLD ;cd -        path=NULL; OLDPWD not set
char	*cd_set_path(const char *arg, t_var *var, bool *is_print_path)
{
	char	*path;

	*is_print_path = false;
	if (!arg)
		path = var->get_value(var, KEY_HOME);
	else
		path = set_path_by_arg(arg, var, is_print_path);
	return (path);
}
