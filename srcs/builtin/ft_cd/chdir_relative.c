#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_mem.h"

static t_deque	*set_path_elems(const char *path)
{
	t_deque	*path_elems;

	path_elems = allocate_path_elems();
	add_split_path_elems(path_elems, path);
	return (path_elems);
}

static char	*get_canonicalize_path(t_deque_node **pop_node, \
									char *canonicalized_path)
{
	char		*tmp;
	const char	*path_segment = (const char *)(*pop_node)->content;

	tmp = canonicalized_path;
	canonicalized_path = cd_canonicalize_path(path_segment, canonicalized_path);
	ft_free(&tmp);
	deque_clear_node(pop_node, del_path_elem);
	return (canonicalized_path);
}

static t_result test_change_directory(const char *arg, \
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
	if (cwd)// do nothing.
	{
		ft_free(&cwd);
		return (FAILURE);
	}
	else
	{
		puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
		return (BREAK);
	}
}

static void	restore_path_and_clean_up(const char *backup_pwd, \
										char **canonicalized_path, \
										t_deque **path_elems)
{
	int	tmp_err;

	cd_exec_chdir(backup_pwd, &tmp_err);
	ft_free(canonicalized_path);
	deque_clear_all(path_elems, del_path_elem);
}

t_result	cd_chdir_from_relative_path(char **absolute_path, \
										const char *arg, \
										const char *path, \
										const char *internal_pwd)
{
	const char		*backup_pwd = internal_pwd;
	t_deque			*path_elems;
	char			*canonicalized_path;
	t_deque_node	*pop_node;
	t_result		result;

	path_elems = set_path_elems(path); // [..]-[..]-[A]-[B]-[..]-
	canonicalized_path = x_ft_strdup(internal_pwd); // todo: for NULL unset PWD && ./minishell
	while (!deque_is_empty(path_elems))
	{
		pop_node = deque_pop_front(path_elems);
		canonicalized_path = get_canonicalize_path(&pop_node, canonicalized_path);
		result = test_change_directory(arg, &canonicalized_path, backup_pwd);
		if (result == FAILURE)
		{
			puterr_cmd_arg_msg(CMD_CD, arg, ERROR_MSG_NO_SUCH_FILE);
			*absolute_path = x_ft_strdup(backup_pwd);
			restore_path_and_clean_up(backup_pwd, &canonicalized_path, &path_elems);
			return (FAILURE);
		}
		if (result == BREAK)
		{
			*absolute_path = x_ft_strjoin(backup_pwd, PATH_DELIMITER_STR);
			*absolute_path = extend_str(*absolute_path, x_ft_strdup(path));
			restore_path_and_clean_up(backup_pwd, &canonicalized_path, &path_elems);
			return (BREAK);
		}
	}
	*absolute_path = canonicalized_path;
	deque_clear_all(&path_elems, del_path_elem);
	return (SUCCESS);
}
