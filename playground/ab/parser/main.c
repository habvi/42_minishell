#include "test.h"
#include "libft.h"

void	error_exit(const char *func_name, const char *msg)
{
	dprintf(STDERR_FILENO, "Error(%s): %s\n", func_name, msg);
	exit(EXIT_FAILURE);
}

bool	next_token_bool(t_token *token, char op)
{
	const char	*str = token->now_token->content;

	if (ft_strnlen(str, 2) == 1 && str[0] == op)
	{
		token->now_token = token->now_token->next;
		return (true);
	}
	return (false);
}

int	next_token_val(t_token *token)
{
	int	val;

	if (token->now_token->kind != NODE_NUM)
		error_exit(__func__, "not num");
	val = token->now_token->val;
	token->now_token = token->now_token->next;
	return (val);
}

int	main(int argc, char **argv)
{
	t_token	token;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Error-!: need 1 argv");
		return (EXIT_FAILURE);
	}
	if (!ft_isdigit(argv[1][0]))
	{
		dprintf(STDERR_FILENO, "Error-!: first argv must digit");
		return (EXIT_FAILURE);
	}
	token = tokenize(argv[1]);
	// print_tken()
	// calc()
	return (0);
}
