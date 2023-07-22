#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

// . or ..
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

static t_result	try_change_directory(const char *arg, \
										char *canonicalized_path, \
										bool is_contain_dot)
{
	t_result	result;
	int			tmp_err;

	result = cd_exec_chdir(canonicalized_path, &tmp_err);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (result == FAILURE)
	{
		if (tmp_err == EACCES)
		{
			puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
			return (FAILURE);
		}
		if (is_contain_dot)
			return (SUCCESS);
		puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
		return (FAILURE);
	}
	return (SUCCESS);
}

// todo: doesn't need pop, just iterate?
char	*cd_create_path_with_pwd(t_deque *path_elems, \
									const char *internal_pwd, \
									const char *arg, \
									t_result *result)
{
	char			*absolute_path;
	t_deque_node	*pop_node;
	bool			is_contain_dot;

	absolute_path = x_ft_strdup(internal_pwd);
	while (!deque_is_empty(path_elems))
	{
		pop_node = deque_pop_front(path_elems);
		is_contain_dot = is_path_segment_dot(pop_node->content);
		absolute_path = get_joined_canonicalize_path(absolute_path, &pop_node);
		*result = try_change_directory(arg, absolute_path, is_contain_dot);
		if (*result == PROCESS_ERROR || *result == FAILURE)
		{
			ft_free(&absolute_path);
			break ;
		}
	}
	return (absolute_path);
}
