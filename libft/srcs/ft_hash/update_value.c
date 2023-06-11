#include <stdlib.h>
#include "ft_deque.h"

// key exist in hash
// free(key, pre-content), update new content
void	update_content_of_key(char **key, \
								void *content, \
								t_deque_node *target_node)
{
	free(*key);
	*key = NULL;
	free(target_node->content);
	target_node->content = content;
}
