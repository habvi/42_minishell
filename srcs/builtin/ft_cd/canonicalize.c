#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"

static void	erase_unnecessary_path_elem(t_deque **path_elems, \
										const char *internal_pwd)
{
	if (is_internal_pwd_relative(internal_pwd))
		erase_dot_path_for_relative(path_elems);
	else
	{
		erase_dot_path(path_elems);
		erase_dot_dot_path(path_elems);
	}
}

static void	handle_double_slash_path(const char *path, char **new_path)
{
	char	*tmp;

	if (is_head_double_slash(path))
	{
		tmp = x_ft_strjoin(PATH_DELIMITER_STR, *new_path);
		ft_free((void **)new_path);
		*new_path = tmp;
	}
}

// 	 PWD         path
// "/home/a"    bb/               -> /home/a/bb
//              ./bb/             -> /home/a/bb
//              ./bb//////        -> /home/a/bb
//              ./bb//////ccc     -> /home/a/bb/ccc
//              ./bb/../../       -> /home
//              ../               -> /home
//              ./                -> /home/a
//              /                 -> /
//              //                -> //
//              ///               -> /
//              ////home          -> /home
//              /home/a/../a/../././      -> /home
//              ../../../../../../../../  -> /
//  NULL                          -> relative
//  ../..                         -> relative
char	*cd_canonicalize_path(const char *internal_pwd, const char *path)
{
	t_deque	*path_elems;
	char	*new_path;

	path_elems = allocate_path_elems();
	path_elems = separate_path_and_join(path, internal_pwd, path_elems);
	erase_unnecessary_path_elem(&path_elems, internal_pwd);
	new_path = convert_path_elems_to_path(path_elems, internal_pwd);
	handle_double_slash_path(path, &new_path);
	destroy_path_elems(&path_elems);
	return (new_path);
}
