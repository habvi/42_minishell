#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

// key exist in hash
// free(key, pre-value), update new value
void	hs_update_value(char **key, \
						void *value, \
						t_deque_node *target_node, \
						void (*del_hash_value)(void **))
{
	t_elem	*elem;

	ft_free(key);
	elem = (t_elem *)target_node->content;
	del_hash_value(&elem->value);
	elem->value = value;
}
