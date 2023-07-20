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

static bool	is_path_segment_dot(const char *const path)
{
	return (ft_streq(PATH_DOT, path) || ft_streq(PATH_DOT_DOT, path));
}

static char	*get_joined_canonicalize_path(char *canonicalized_path, \
											t_deque_node **pop_node)
{
	char		*tmp;
	const char	*path_segment = (const char *)(*pop_node)->content;

	tmp = canonicalized_path;
	canonicalized_path = cd_canonicalize_path(path_segment, canonicalized_path);
	ft_free(&tmp);
	deque_clear_node(pop_node, del_path_elem);
	return (canonicalized_path);
}

static void	restore_path_and_clean_up(const char *backup_pwd, \
										t_deque **path_elems)
{
	int	tmp_err;

	cd_exec_chdir(backup_pwd, &tmp_err);
	deque_clear_all(path_elems, del_path_elem);
}

t_result	cd_chdir_from_relative_path(char **absolute_path, \
										const char *arg, \
										const char *path, \
										const char *internal_pwd)
{
	t_deque			*path_elems;
	t_deque_node	*pop;
	bool			is_contain_dot;
	const char		*backup_pwd = internal_pwd;
	t_result		result;

	// if !PWD
	path_elems = set_path_elems(path); // [..]-[..]-[A]-[B]-[..]-
	*absolute_path = x_ft_strdup(internal_pwd);
	while (!deque_is_empty(path_elems))
	{
		pop = deque_pop_front(path_elems);
		is_contain_dot = is_path_segment_dot(pop->content);
		*absolute_path = get_joined_canonicalize_path(*absolute_path, &pop);
		result = try_change_directory(arg, *absolute_path, is_contain_dot);
		if (result == FAILURE)
		{
			restore_path_and_clean_up(backup_pwd, &path_elems);
			return (FAILURE);
		}
	}
	result = check_current_exist(arg, absolute_path);
	if (result == FAILURE || result == BREAK)
	{
		set_absolute_path_in_error(absolute_path, backup_pwd, path, result);
		restore_path_and_clean_up(backup_pwd, &path_elems);
		return (result);
	}
	deque_clear_all(&path_elems, del_path_elem);
	return (SUCCESS);
}
