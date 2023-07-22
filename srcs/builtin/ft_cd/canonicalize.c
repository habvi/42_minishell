#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"

#include "ft_string.h"

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
// "/home/aaa"  libft/            -> /home/aaa/libft
//              ./libft/          -> /home/aaa/libft
//              ./libft//////     -> /home/aaa/libft
//              ./libft//////srcs -> /home/aaa/libft/srcs
//              ./libft/../../    -> /home
//              ../               -> /home
//              ./                -> /home/aaa
//              //                -> /
//              //                -> //
//              ///               -> /
//              ////home          -> /home
//              /home/aaa/../aaa/../././  -> /home
//              ../../../../../../../../  -> /
//  PWD=NULL                      -> unspecified
char	*cd_canonicalize_path(const char *path, const char *internal_pwd)
{
	t_deque	*path_elems;
	char	*absolute_path;

	// if (!internal_pwd)
	// 	return (); // todo: for unset PWD & ./minishell
	path_elems = allocate_path_elems();
	path_elems = separate_path_and_join(path, internal_pwd, path_elems);
	erase_unnecessary_path_elem(&path_elems, internal_pwd);
	absolute_path = convert_path_elems_to_absolute_path(path_elems, internal_pwd);
	// ft_dprintf(2, "%s: %s\n", __func__, absolute_path);
	handle_double_slash_path(path, &absolute_path);
	destroy_path_elems(path_elems);
	return (absolute_path);
}
