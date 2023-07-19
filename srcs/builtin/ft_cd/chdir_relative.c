#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"

static t_deque	*set_path_elems(const char *path)
{
	t_deque	*path_elems;

	path_elems = allocate_path_elems();
	add_split_path_elems(path_elems, path);
	return (path_elems);
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

static t_result	test_change_directory(const char *arg, \
										char **canonicalized_path,
										const char *backup_pwd)
{
	t_result	result;
	int			tmp_err;
	char		*cwd;

	result = cd_exec_chdir(*canonicalized_path, &tmp_err);
	if (result == SUCCESS)
		return (SUCCESS);
	if (tmp_err == EACCES)
	{
		puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
		return (FAILURE);
	}
	(void)backup_pwd;
	// result = cd_exec_chdir(backup_pwd, &tmp_err);
	cwd = get_working_directory(CMD_CD);
	if (cwd)
	{
		ft_free(&cwd);
		puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
		return (FAILURE);
	}
	return (BREAK);
}

t_result	cd_chdir_from_relative_path(char **absolute_path, \
										const char *arg, \
										const char *path, \
										const char *internal_pwd)
{
	t_deque			*path_elems;
	t_deque_node	*pop;
	const char		*backup_pwd = internal_pwd;
	t_result		result;

	path_elems = set_path_elems(path); // [..]-[..]-[A]-[B]-[..]-
	*absolute_path = x_ft_strdup(internal_pwd);
	while (!deque_is_empty(path_elems))
	{
		pop = deque_pop_front(path_elems);
		*absolute_path = get_joined_canonicalize_path(*absolute_path, &pop);
		result = test_change_directory(arg, absolute_path, backup_pwd);
		if (result == FAILURE || result == BREAK)
		{
			set_absolute_path_in_error(absolute_path, backup_pwd, path, result);
			restore_path_and_clean_up(backup_pwd, absolute_path, &path_elems);
			return (result);
		}
	}
	deque_clear_all(&path_elems, del_path_elem);
	return (SUCCESS);
}
