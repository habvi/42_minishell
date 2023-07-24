#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

static char	*dup_path_prefix(const char *path, const char *internal_pwd)
{
	if (is_absolute_path(path))
		return (x_ft_strdup(PATH_DELIMITER_STR));
	return (x_ft_strdup(internal_pwd));
}

// define "//" -> error in norm 3.3.51, fixed 3.3.53
static t_deque	*set_path_elems(const char *path)
{
	t_deque			*path_elems;
	t_deque_node	*new_node;

	path_elems = allocate_path_elems();
	add_split_path_elems(path_elems, path);
	if (is_head_double_slash(path))
	{
		new_node = deque_node_new(x_ft_strdup("//"));
		deque_add_back(path_elems, new_node);
	}
	return (path_elems);
}

// . or ..
static bool	is_path_segment_dot_or_dot_dot(const char *const path)
{
	return (ft_streq(PATH_DOT, path) || ft_streq(PATH_DOT_DOT, path));
}

static char	*get_joined_canonicalize_path(char **pre_path, \
											const char *path_segment)
{
	char	*canonicalized_path;

	canonicalized_path = cd_canonicalize_path(*pre_path, path_segment);
	ft_free((void **)pre_path);
	return (canonicalized_path);
}

// path_elems : ../../A/B/../ -> [..]-[..]-[A]-[B]-[..]
char	*cd_create_path_with_pwd(const char *arg, \
									const char *path, \
									const char *internal_pwd, \
									t_result *result)
{
	char			*new_path;
	t_deque			*path_elems;
	t_deque_node	*node;
	char			*path_segment;
	bool			is_contain_dot;

	new_path = dup_path_prefix(path, internal_pwd);
	path_elems = set_path_elems(path);
	node = path_elems->node;
	while (node)
	{
		path_segment = (char *)node->content;
		is_contain_dot = is_path_segment_dot_or_dot_dot(path_segment);
		new_path = get_joined_canonicalize_path(&new_path, path_segment);
		*result = chack_is_valid_directory(arg, path, new_path, is_contain_dot);
		if (*result == PROCESS_ERROR || *result == FAILURE)
		{
			deque_clear_all(&path_elems, del_path_elem);
			return (new_path);
		}
		node = node->next;
	}
	*result = chack_is_valid_directory(arg, path, new_path, is_contain_dot);
	deque_clear_all(&path_elems, del_path_elem);
	return (new_path);
}
