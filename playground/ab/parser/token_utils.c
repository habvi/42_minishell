#include "test.h"

void	print_token(t_token *token)
{
	while (token)
	{
		dprintf(STDERR_FILENO, "%s\n", token->str);
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

void	error_exit(const char *func_name, const char *msg)
{
	dprintf(STDERR_FILENO, "Error(%s): %s\n", func_name, msg);
	exit(EXIT_FAILURE);
}
