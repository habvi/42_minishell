#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

// stack
void	erase_dot_path(t_deque **path_elems)
{
	t_deque			*new_path_elems;
	t_deque_node	*pop_node;
	char			*path_elem;

	new_path_elems = allocate_path_elems();
	while (!deque_is_empty(*path_elems))
	{
		pop_node = deque_pop_front(*path_elems);
		path_elem = (char *)pop_node->content;
		if (ft_streq(path_elem, PATH_DOT))
		{
			deque_clear_node(&pop_node, del_path_elem);
			continue ;
		}
		deque_add_back(new_path_elems, pop_node);
	}
	destroy_path_elems(*path_elems);
	*path_elems = new_path_elems;
}

// stack
void	erase_dot_dot_path(t_deque **path_elems)
{
	t_deque			*new_path_elems;
	t_deque_node	*pop_node;
	char			*path_elem;

	new_path_elems = allocate_path_elems();
	while (!deque_is_empty(*path_elems))
	{
		pop_node = deque_pop_front(*path_elems);
		path_elem = (char *)pop_node->content;
		if (ft_streq(path_elem, PATH_DOT_DOT))
		{
			deque_clear_node(&pop_node, del_path_elem);
			pop_node = deque_pop_back(new_path_elems);
			deque_clear_node(&pop_node, del_path_elem);
			continue ;
		}
		deque_add_back(new_path_elems, pop_node);
	}
	destroy_path_elems(*path_elems);
	*path_elems = new_path_elems;
}

static bool	is_head_double_slash(const char *path)
{
	return (path[0] == PATH_DELIMITER_CHR \
			&& path[1] == PATH_DELIMITER_CHR \
			&& path[2] != PATH_DELIMITER_CHR);
}

#include <stdio.h>
void	handle_double_slash_path(const char *path, char **absolute_path)
{
	char	*new_path;

	if (is_head_double_slash(path))
	{
		new_path = ft_strjoin(PATH_DELIMITER_STR, *absolute_path);
		if (!new_path)
			ft_abort();
		ft_free(absolute_path);
		*absolute_path = new_path;
	}
}
