#include "test.h"
#include "libft.h"

// static void	set_token_node(t_token_node *token, char *str)
// {
// 	token->head_token->val = 0;
// 	if (is_eqaul_strings(str, "+"))
// 		token->head_token->kind = NODE_ADD;
// 	else if (is_eqaul_strings(str, "-"))
// 		token->head_token->kind = NODE_SUB;
// 	else if (is_eqaul_strings(str, "*"))
// 		token->head_token->kind = NODE_MUL;
// 	else if (is_eqaul_strings(str, "/"))
// 		token->head_token->kind = NODE_DIV;
// 	else if (ft_isdigit(*str))
// 	{
// 		token->head_token->kind = NODE_NUM;
// 		if (!ft_atoi(str, &token->head_token->val))
// 		{
// 			dprintf(STDERR_FILENO, "argv overflow");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 	{
// 		dprintf(STDERR_FILENO, "failed tokenize");
// 		exit(EXIT_FAILURE);
// 	}
// }

// static t_deque_node	*token_new(char *str)
// {
// 	t_deque_node	*node;
// 	t_token_node	*token;

// 	node = (t_deque_node *)malloc(sizeof(t_deque_node));
// 	if (!node)
// 		exit(EXIT_FAILURE);
// 	set_token_node(token, str);
// 	node->content = token;
// 	node->next = NULL;
// 	node->prev = NULL;
// 	return (node);
// }

// void	tokenize(char *str, t_deque **head_token)
// {
// 	char			**split_str;
// 	size_t			i;
// 	t_deque_node	*node;

// 	split_str = ft_split(str, ' ');
// 	if (split_str == NULL)
// 		exit(EXIT_FAILURE);
// 	*head_token = deque_new();
// 	if (*head_token == NULL)
// 		exit(EXIT_FAILURE);
// 	i = 0;
// 	while (split_str[i])
// 	{
// 		node = token_new(split_str[i]);
// 		if (node == NULL)
// 			exit(EXIT_FAILURE);
// 		deque_add_back(*head_token, node);
// 		i++;
// 	}
// 	free(split_str);
// 	split_str = NULL;
// }
