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
	split_and_add_dq(path_elems, path);
	return (path_elems);
}

// todo: func name
static char	*get_canonicalize_path(t_deque_node **pop_node, \
									char *canonicalized_path)
{
	char		*tmp;
	const char	*path_segment = (const char *)(*pop_node)->content;

	tmp = canonicalized_path;
	// ft_dprintf(2, "%d: [%s] [%s]\n", __LINE__, canonicalized_path, path_segment);
	canonicalized_path = cd_canonicalize_path(path_segment, canonicalized_path);
	// ft_dprintf(2, "%d: [%s] [%s]\n", __LINE__, canonicalized_path, path_segment);
	ft_free(&tmp);
	deque_clear_node(pop_node, del_path_elem);
	return (canonicalized_path);
}

// todo: func name
static t_result chdir_from_relative_path_inter(const char *arg, \
												char **canonicalized_path,
												const char *backup_pwd)
{
	t_result	result;
	int			tmp_err;

	result = cd_change_dir_to_valid_path(*canonicalized_path, &tmp_err);
	if (result == SUCCESS)
		return (SUCCESS);
	if (tmp_err == EACCES)
	{
		puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
		// ft_dprintf(2, "%d: [%s]\n", __LINE__, *canonicalized_path);
		return (FAILURE);
	}
	(void)backup_pwd;
	// result = cd_change_dir_to_valid_path(backup_pwd, &tmp_err);
	// getcwd() failed... "cd nothing"
	if (getcwd(NULL, 1)) // todo: buf?
	{
		// do nothing.
		// ft_dprintf(2, "%d: [%s]\n", __LINE__, *canonicalized_path);
		return (FAILURE);
	}
	else
	{
		puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
		// ft_dprintf(2, "%d: [%s]\n", __LINE__, *canonicalized_path);
		return (BREAK);
	}
}

// todo: func name
static void	clear_for_return(char **canonicalized_path, t_deque **path_elems)
{
	ft_free(canonicalized_path);
	deque_clear_all(path_elems, del_path_elem);
}

// todo: func name
static void	set_error_for_failure(const char *arg, \
									const char *backup_pwd, \
									char **canonicalized_path, \
									t_deque **path_elems)
{
	int	tmp_err;

	cd_change_dir_to_valid_path(backup_pwd, &tmp_err);
	puterr_cmd_arg_msg(CMD_CD, arg, ERROR_MSG_NO_SUCH_FILE);
	// ft_dprintf(2, "%d: [%s]\n", __LINE__, *canonicalized_path);
	clear_for_return(canonicalized_path, path_elems);
}

// todo: func name
static void	set_error_for_break(const char *backup_pwd, \
								char **canonicalized_path, \
								t_deque **path_elems)
{
	int	tmp_err;

	cd_change_dir_to_valid_path(backup_pwd, &tmp_err);
	// ft_dprintf(2, "%d: [%s]\n", __LINE__, backup_pwd);
	// ft_dprintf(2, "%d: [%s]\n", __LINE__, *canonicalized_path);
	clear_for_return(canonicalized_path, path_elems);
}

t_result	cd_chdir_from_relative_path(const char *arg, \
										const char *path, \
										char **absolute_path, \
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
		result = chdir_from_relative_path_inter(arg, &canonicalized_path, backup_pwd);
		if (result == FAILURE)
		{
			*absolute_path = x_ft_strdup(backup_pwd);
			set_error_for_failure(arg, backup_pwd, &canonicalized_path, &path_elems);
			return (FAILURE);
		}
		if (result == BREAK)
		{
			*absolute_path = x_ft_strjoin(backup_pwd, PATH_DELIMITER_STR);
			*absolute_path = extend_str(*absolute_path, x_ft_strdup(path));
			set_error_for_break(backup_pwd, &canonicalized_path, &path_elems);
			return (BREAK);
		}
	}
	*absolute_path = canonicalized_path;
	deque_clear_all(&path_elems, del_path_elem);
	return (SUCCESS);
}
