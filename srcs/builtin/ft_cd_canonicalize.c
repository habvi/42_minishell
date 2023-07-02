#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

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

static t_deque	*separate_path_and_join(const char *path, t_context *context)
{
	t_deque	*path_elems;

	path_elems = deque_new();
	if (!path_elems)
		ft_abort();
	if (!is_absolute_path(path))
	{
		if (context->internal_pwd)
			split_and_add_dq(path_elems, context->internal_pwd);
	}
	split_and_add_dq(path_elems, path);
	return (path_elems);
}

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

static char	*convert_path_elems_to_absolute_path(t_deque *path_elems)
{
	const size_t	len_path = calc_len_path(path_elems);
	size_t			i;
	t_deque_node	*node;
	char			*absolute_path;
	char			*path_elem;
	size_t			len_path_elem;

	absolute_path = (char *)x_malloc(sizeof(char) * (len_path + 1));
	if (!absolute_path)
		ft_abort();
	i = 0;
	ft_strlcpy_void(&absolute_path[i], PATH_DELIMITER_STR, ft_strlen(PATH_DELIMITER_STR) + 1);
	i++;
	node = path_elems->node;
	while (node)
	{
		path_elem = (char *)node->content;
		len_path_elem = ft_strlen(path_elem);
		ft_strlcpy_void(&absolute_path[i], path_elem, len_path_elem + 1); // todo
		i += len_path_elem;
		if (node->next)
		{
			ft_strlcpy_void(&absolute_path[i], PATH_DELIMITER_STR, ft_strlen(PATH_DELIMITER_STR) + 1);
			i++;
		}
		node = node->next;
	}
	return (absolute_path);
}

// todo
static void	del(void *content)
{
	ft_free(&content);
}

// 	 PWD         path
// "/home/aaa"  libft/            -> /home/aaa/libft
//              ./libft/          -> /home/aaa/libft
//              ./libft//////     -> /home/aaa/libft
//              ./libft//////srcs -> /home/aaa/libft/srcs
//              ./libft/../../    -> /home
//              ../               -> /home
//              ./                -> /home/aaa
//              /home/../aaa/../  -> /
//              ../../
char	*cd_canonicalize_path(const char *path, t_context *context)
{
	t_deque	*path_elems;
	char	*absolute_path;

	path_elems = separate_path_and_join(path, context);
	// erase .
	// erase path/../
	absolute_path = convert_path_elems_to_absolute_path(path_elems);
	deque_clear_all(&path_elems, del);
	return (absolute_path);
}
