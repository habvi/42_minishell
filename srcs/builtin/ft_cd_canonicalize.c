#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"

void	del_path_elem(void *content)
{
	ft_free(&content);
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
char	*cd_canonicalize_path(const char *path, t_context *context)
{
	t_deque	*path_elems;
	char	*absolute_path;

	path_elems = separate_path_and_join(path, context);
	erase_dot_path(&path_elems);
	erase_dot_dot_path(&path_elems);
	absolute_path = convert_path_elems_to_absolute_path(path_elems);
	absolute_path = handle_double_slash_path(path, absolute_path);
	deque_clear_all(&path_elems, del_path_elem);
	return (absolute_path);
}
