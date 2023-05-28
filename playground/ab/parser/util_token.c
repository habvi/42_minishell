#include "test.h"

void	print_token(t_token *token)
{
	while (token)
	{
		printf("%s\n", token->str);
		token = token->next;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp);
	}
}
