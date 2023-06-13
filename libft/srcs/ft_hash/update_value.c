#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

// key exist in hash
// free(key, pre-content), update new content
void	update_content_of_key(char **key, \
								void *content, \
								t_deque_node *target_node)
{
	t_elem	*elem;

	ft_free(*key);
	elem = (t_elem *)target_node->content;
	elem->del_content(elem->content);
	elem->content = content;
}
