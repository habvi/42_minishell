#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"

// key exist in hash
// free(key, pre-content), update new content
void	update_content_of_key(char **key, \
								void *content, \
								t_deque_node *target_node)
{
	t_elem	*elem;

	(void)key;
	// free(*key);
	// *key = NULL;
	elem = (t_elem *)target_node->content;
	// free(elem->content);
	elem->content = content;
}
