#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"

t_deque	*allocate_path_elems(void)
{
	t_deque	*path_elems;

	path_elems = deque_new();
	if (!path_elems)
		ft_abort();
	return (path_elems);
}

bool	is_internal_pwd_relative(const char *internal_pwd)
{
	if (!internal_pwd)
		return (true);
	return (!is_absolute_path(internal_pwd));
}

static void	erase_unnecessary_path_elem(t_deque **path_elems, const char *internal_pwd)
{
	if (is_internal_pwd_relative(internal_pwd))
		erase_dot_path_for_relative(path_elems);
	else
	{
		erase_dot_path(path_elems);
		erase_dot_dot_path(path_elems);
	}
}

void	del_path_elem(void *content)
{
	ft_free(&content);
}

void	destroy_path_elems(t_deque *path_elems)
{
	deque_clear_all(&path_elems, del_path_elem);
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
	new_path = convert_path_elems_to_absolute_path(path_elems, internal_pwd);
	handle_double_slash_path(path, &new_path);
	destroy_path_elems(path_elems);
	return (new_path);
}
