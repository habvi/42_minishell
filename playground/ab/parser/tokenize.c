#include <ctype.h> // isdigit
#include "test.h"
#include "libft.h"

static t_node_kind	get_kind(char *str)
{
	if (str == NULL)
		return (NODE_EOF);
	if (is_equal_strings(str, "+"))
		return (NODE_ADD);
	if (is_equal_strings(str, "-"))
		return (NODE_SUB);
	if (is_equal_strings(str, "*"))
		return (NODE_MUL);
	if (is_equal_strings(str, "/"))
		return (NODE_DIV);
	return (NODE_NONE);
}

static t_token	*token_new(char *str)
{
	t_token	*token;
	int		num;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		error_exit(__func__, "failed to allocate");
	token->str = str;
	token->next = NULL;
	if (str && ft_atoi(str, &num))
	{
		token->kind = NODE_NUM;
		token->val = num;
	}
	else
	{
		token->kind = get_kind(str);
		token->val = 0;
	}
	return (token);
}

static void	add_back_token(t_token *head, t_token *new_token)
{
	while (head->next)
		head = head->next;
	head->next = new_token;
}

t_token *tokenize(char *p)
{
	char	**split_str;
	size_t	i;
	t_token	token = {.str = NULL, .kind = NODE_NONE, .val = 0, .next = NULL};

	if (!isdigit(*p))
		error_exit(__func__, "first must digit");
	split_str = ft_split(p, ' ');
	i = 0;
	while (split_str[i])
	{
		add_back_token(&token, token_new(split_str[i]));
		split_str[i] = NULL;
		i++;
	}
	add_back_token(&token, token_new(NULL));
	free(split_str);
	return (token.next);
}
