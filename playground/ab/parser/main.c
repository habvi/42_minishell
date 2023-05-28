#include "test.h"
#include "libft.h"

// bool	next_token_bool(t_token *token, char op)
// {
// 	const char	*str = token->now_token->content;

// 	if (ft_strnlen(str, 2) == 1 && str[0] == op)
// 	{
// 		token->now_token = token->now_token->next;
// 		return (true);
// 	}
// 	return (false);
// }

// int	next_token_val(t_token *token)
// {
// 	int	val;

// 	if (token->now_token->kind != NODE_NUM)
// 		error_exit(__func__, "not num");
// 	val = token->now_token->val;
// 	token->now_token = token->now_token->next;
// 	return (val);
// }

int	main(int argc, char **argv)
{
	t_token	*token;

	if (argc != 2)
		error_exit(__func__, "need 1 argv");
	if (!ft_isdigit(argv[1][0]))
		error_exit(__func__, "first argv must digit");
	token = tokenize(argv[1]);
	print_token(token);
	// parse_to_ast()
	// calc()
	free_token(token);
	return (EXIT_SUCCESS);
}
