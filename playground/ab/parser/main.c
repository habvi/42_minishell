#include "test.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_token		*token;
	t_token		*token_head;
	t_ast_node	*ast;
	int			result;

	if (argc != 2)
		error_exit(__func__, "need 1 argv");
	if (!ft_isdigit(argv[1][0]))
		error_exit(__func__, "first argv must digit");

	token = tokenize(argv[1]);
	print_token(token);

	token_head = token;
	ast = create_ast(token);
	free_token(token_head); // free(token->str)
	print_ast(ast);

	result = calc_from_ast(ast);
	free_ast_node(ast);
	printf("[calc result: %d]\n", result);
	return (EXIT_SUCCESS);
}
