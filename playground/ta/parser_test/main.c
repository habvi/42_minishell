#include "test.h"

int	main(int argc, char **argv)
{
	char	**split;
	t_token	*token;
    t_token *token_head;
	t_tree	*tree;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, MSG_USAGE);
		return (1);
	}
	split = ft_split(argv[1], ' ');
	print_split(split);

	token = tokenize(split);
	print_token(token);

    token_head = token;
	tree = expression(&token_head);
	print_tree(tree);

	free_2d_array(&split);
	free_token(&token);
	free_tree(&tree);
//	system("leaks a.out");
	return (0);
}
