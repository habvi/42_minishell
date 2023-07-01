#include "ms_var.h"
#include "ft_deque.h"
#include "ft_hash.h"

void	update_attr(t_var *var, const char *key, t_var_attr attr)
{
	t_deque_node	*node;
	t_elem			*elem;
	t_var_info		*var_info;

	if (var_is_key_exist(var, key))
	{
		node = hs_find_key(var->hash, key);
		elem = (t_elem *)node->content;
		var_info = (t_var_info *)elem->value;
		var_info->attr = attr;
	}
	else
		var->add(var, key, NULL);
}