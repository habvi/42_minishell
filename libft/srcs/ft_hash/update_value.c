#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"

// key exist in hash
// free(key, pre-content), update new content
void	update_content_of_key(t_deque_node *target_node, \
								char **key, \
								void *content)
{
	t_elem	*elem;

	free(*key);
	*key = NULL;
	elem = (t_elem *)target_node->content;
	free(elem->content);
	elem->content = content;
}
