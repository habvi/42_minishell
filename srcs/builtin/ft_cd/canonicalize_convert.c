#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_string.h"
#include "ft_sys.h"

// all len path_elems + number of delimiter("/")
// absolute pwd -> /path
// relative pwd -> path
static size_t	calc_len_path(t_deque *path_elems, const char *internal_pwd)
{
	size_t			len_path;
	t_deque_node	*node;

	if (is_internal_pwd_relative(internal_pwd))
		len_path = 0;
	else
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

// todo: func name. not only absolute
static char	*allocate_absolute_path(t_deque *path_elems, \
									const char *internal_pwd)
{
	const size_t	len_path = calc_len_path(path_elems, internal_pwd);
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

static bool	is_last_path_elems(t_deque_node *node)
{
	return (!node->next);
}

char	*convert_path_elems_to_absolute_path(t_deque *path_elems, \
												const char *internal_pwd)
{
	char			*absolute_path;
	size_t			i;
	t_deque_node	*node;
	char			*path_elem;

	absolute_path = allocate_absolute_path(path_elems, internal_pwd);
	i = 0;
	if (is_absolute_path(internal_pwd))
		strlcpy_path_elem(absolute_path, &i, PATH_DELIMITER_STR);
	node = path_elems->node;
	while (node)
	{
		path_elem = (char *)node->content;
		strlcpy_path_elem(absolute_path, &i, path_elem);
		if (!is_last_path_elems(node))
			strlcpy_path_elem(absolute_path, &i, PATH_DELIMITER_STR);
		node = node->next;
	}
	return (absolute_path);
}
