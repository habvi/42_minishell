#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

static t_deque	*set_path_elems(const char *path)
{
	t_deque	*path_elems;

	path_elems = allocate_path_elems();
	add_split_path_elems(path_elems, path);
	return (path_elems);
}

static bool	is_internal_pwd_relative(const char *internal_pwd)
{
	if (!internal_pwd)
		return (true);
	return (!is_absolute_path(internal_pwd));
}

// return error after this function, so not implement chdir error handling here.
static void	restore_path_and_clean_up(const char *internal_pwd, \
										t_deque **path_elems)
{
	int	tmp_err;

	cd_exec_chdir(internal_pwd, &tmp_err);
	deque_clear_all(path_elems, del_path_elem);
}

// path_elems : ../../A/B/../ -> [..]-[..]-[A]-[B]-[..]
t_result	cd_chdir_from_relative_path(char **new_path, \
										const char *arg, \
										const char *path, \
										const char *internal_pwd)
{
	t_deque		*path_elems;
	t_result	result;

	result = SUCCESS;
	path_elems = set_path_elems(path);
	if (is_internal_pwd_relative(internal_pwd))
		*new_path = cd_create_path_with_relative_pwd(); // todo
	else
	{
		*new_path = cd_create_path_with_absolute_pwd(\
								path_elems, internal_pwd, arg, &result);
		if (result == PROCESS_ERROR || result == FAILURE)
		{
			restore_path_and_clean_up(internal_pwd, &path_elems);
			return (result);
		}
		result = cd_check_current_exist(arg, new_path, internal_pwd, path);
	}
	deque_clear_all(&path_elems, del_path_elem);
	return (result);
}
