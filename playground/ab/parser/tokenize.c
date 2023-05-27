#include "test.h"
#include "deque.h"
#include "libft.h"

void	tokenize(char *str, t_deque **head_token)
{
	char			**split_str;
	size_t			i;
	t_deque_node	*node;

	split_str = ft_split(str, ' ');
	if (split_str == NULL)
		exit(EXIT_FAILURE);
	*head_token = deque_new();
	if (*head_token == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (split_str[i])
	{
		node = deque_node_new(split_str[i]);
		if (node == NULL)
			exit(EXIT_FAILURE);
		deque_add_back(*head_token, node);
		i++;
	}
	free(split_str);
	split_str = NULL;
}
