#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ms_var.h"
#include "ft_string.h"
#include "ft_mem.h"

static bool	is_arg_head_dot(const char *arg)
{
	return (arg[0] == CHAR_PATH_DOT);
}

// /dir ./ ../
static bool	is_skip_cdpath_search(const char *arg)
{
	if (is_absolute_path(arg))
		return (true);
	if (is_arg_head_dot(arg))
		return (true);
	return (false);
}

static bool	is_var_cdpath_exist(t_var *var)
{
	return (var_is_key_exist(var, KEY_CDPATH));
}

static char	*search_command_path(const char *arg, t_var *var)
{
	char	*cdpath;
	char	*valid_path;

	cdpath = create_split_src_paths(var, KEY_CDPATH);
	valid_path = create_executable_or_accessible_path(cdpath, \
														(const char *const)arg, \
														test_opendir_strict);
	ft_free(&cdpath);
	return (valid_path);
}

// /dir
// file
// file/
// ./file
char	*search_cdpath(const char *arg, t_var *var, bool *is_print_path)
{
	char	*path;

	if (is_skip_cdpath_search(arg))
		return (x_ft_strdup(arg));
	if (is_var_cdpath_exist(var))
	{
		path = search_command_path(arg, var);
		if (path)
		{
			*is_print_path = true;
			return (path);
		}
	}
	path = x_ft_strdup(arg);
	return (path);
}
