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

void	del_path_elem(void *content)
{
	ft_free(&content);
}

void	destroy_path_elems(t_deque *path_elems)
{
	deque_clear_all(&path_elems, del_path_elem);
}

bool	is_internal_pwd_relative(const char *internal_pwd)
{
	if (!internal_pwd)
		return (true);
	return (!is_absolute_path(internal_pwd));
}

// todo: use ft_strncmp?
bool	is_head_double_slash(const char *path)
{
	return (path[0] == PATH_DELIMITER_CHR \
			&& path[1] == PATH_DELIMITER_CHR \
			&& path[2] != PATH_DELIMITER_CHR);
}
