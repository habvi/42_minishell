#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

void	erase_dot_path(t_deque **dq)
{
	t_deque			*stack;
	t_deque_node	*pop_node;
	char			*path_elem;

	stack = deque_new();
	if (!stack)
		ft_abort();
	while (!deque_is_empty(*dq))
	{
		pop_node = deque_pop_front(*dq);
		path_elem = (char *)pop_node->content;
		if (ft_streq(path_elem, PATH_DOT))
		{
			deque_clear_node(&pop_node, del_path_elem);
			continue ;
		}
		deque_add_back(stack, pop_node);
	}
	deque_clear_all(dq, del_path_elem);
	*dq = stack;
}

void	erase_dot_dot_path(t_deque **dq)
{
	t_deque			*stack;
	t_deque_node	*pop_node;
	char			*path_elem;

	stack = deque_new();
	if (!stack)
		ft_abort();
	while (!deque_is_empty(*dq))
	{
		pop_node = deque_pop_front(*dq);
		path_elem = (char *)pop_node->content;
		if (ft_streq(path_elem, PATH_DOT_DOT))
		{
			deque_clear_node(&pop_node, del_path_elem);
			pop_node = deque_pop_back(stack);
			deque_clear_node(&pop_node, del_path_elem);
			continue ;
		}
		deque_add_back(stack, pop_node);
	}
	deque_clear_all(dq, del_path_elem);
	*dq = stack;
}

static bool	is_head_double_slash(const char *path)
{
	return (path[0] == PATH_DELIMITER_CHR \
			&& path[1] == PATH_DELIMITER_CHR \
			&& path[2] != PATH_DELIMITER_CHR);
}

char	*handle_double_slash_path(const char *path, char *absolute_path)
{
	char	*new_path;

	if (is_head_double_slash(path))
	{
		new_path = ft_strjoin(PATH_DELIMITER_STR, absolute_path);
		if (!new_path)
			ft_abort();
		ft_free(&absolute_path);
		return (new_path);
	}
	return (absolute_path);
}
