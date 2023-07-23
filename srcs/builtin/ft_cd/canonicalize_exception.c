#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

static bool	is_head_path_dot(t_deque *path_elems)
{
	const char	*path_elem = path_elems->node->content;

	return (ft_streq(path_elem, PATH_DOT));
}

// ./../..  ->  ../..
static void	erase_head_dot(t_deque *new_path_elems)
{
	t_deque_node	*pop_node;

	if (new_path_elems->size >= 2 && is_head_path_dot(new_path_elems))
	{
		pop_node = deque_pop_front(new_path_elems);
		deque_clear_node(&pop_node, del_path_elem);
	}
}

// stack
// ././        -> .
// .././.././. -> ../..
// ./../..     -> ../.. (erase_head_dot)
void	erase_dot_path_for_relative(t_deque **path_elems)
{
	t_deque			*new_path_elems;
	t_deque_node	*pop_node;
	char			*path_elem;

	new_path_elems = allocate_path_elems();
	while (!deque_is_empty(*path_elems))
	{
		pop_node = deque_pop_front(*path_elems);
		path_elem = (char *)pop_node->content;
		if (ft_streq(path_elem, PATH_DOT) && !deque_is_empty(new_path_elems))
		{
			deque_clear_node(&pop_node, del_path_elem);
			continue ;
		}
		deque_add_back(new_path_elems, pop_node);
	}
	erase_head_dot(new_path_elems);
	destroy_path_elems(*path_elems);
	*path_elems = new_path_elems;
}

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
