#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

static void	add_split_path_to_path_elems(t_deque *path_elems, char **split_path)
{
	size_t			i;
	t_deque_node	*node;

	i = 0;
	while (split_path[i])
	{
		node = deque_node_new((void *)split_path[i]);
		deque_add_back(path_elems, node);
		split_path[i] = NULL;
		i++;
	}
}

static void	split_and_add_dq(t_deque *path_elems, const char *path)
{
	char	**split_path;

	split_path = ft_split(path, PATH_DELIMITER_CHR);
	if (!split_path)
		ft_abort();
	add_split_path_to_path_elems(path_elems, split_path);
	ft_free(&split_path);
}

t_deque	*separate_path_and_join(const char *path, \
								const char *internal_pwd, \
								t_deque *path_elems)
{
	if (!is_absolute_path(path))
	{
		if (internal_pwd)
			split_and_add_dq(path_elems, internal_pwd);
	}
	split_and_add_dq(path_elems, path);
	return (path_elems);
}
