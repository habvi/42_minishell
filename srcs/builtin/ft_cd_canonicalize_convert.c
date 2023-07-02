#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_string.h"
#include "ft_sys.h"

static size_t	calc_len_path(t_deque *path_elems)
{
	size_t			len_path;
	t_deque_node	*node;

	len_path = 1;
	node = path_elems->node;
	while (node)
	{
		len_path += ft_strlen((char *)node->content);
		node = node->next;
	}
	if (path_elems->size)
		len_path += path_elems->size - 1;
	return (len_path);
}

static char	*allocate_absolute_path(t_deque *path_elems)
{
	const size_t	len_path = calc_len_path(path_elems);
	char			*absolute_path;

	absolute_path = (char *)x_malloc(sizeof(char) * (len_path + 1));
	if (!absolute_path)
		ft_abort();
	return (absolute_path);
}

static void	strlcpy_path_elem(char *absolute_path, \
								size_t *i, \
								const char *path_elem)
{
	const size_t	len_path_elem = ft_strlen(path_elem);

	ft_strlcpy_void(&absolute_path[*i], path_elem, len_path_elem + 1);
	(*i) += len_path_elem;
}

char	*convert_path_elems_to_absolute_path(t_deque *path_elems)
{
	char			*absolute_path;
	size_t			i;
	t_deque_node	*node;
	char			*path_elem;

	absolute_path = allocate_absolute_path(path_elems);
	i = 0;
	strlcpy_path_elem(absolute_path, &i, PATH_DELIMITER_STR);
	node = path_elems->node;
	while (node)
	{
		path_elem = (char *)node->content;
		strlcpy_path_elem(absolute_path, &i, path_elem);
		if (node->next)
			strlcpy_path_elem(absolute_path, &i, PATH_DELIMITER_STR);
		node = node->next;
	}
	return (absolute_path);
}
