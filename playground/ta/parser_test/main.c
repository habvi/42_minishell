#include "test.h"

static void	print_split(char **split)
{
	size_t	i;

	i = 0;
	dprintf(STDERR_FILENO, "%-12s:[", "split");
	while (split && split[i])
	{
		dprintf(STDERR_FILENO, "%s", split[i]);
		i++;
		if (split[i])
			dprintf(STDERR_FILENO, ", ");
	}
	dprintf(STDERR_FILENO, "]\n");
}

int	main(int argc, char **argv)
{
	char	**split;
	t_token	*token;
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

	tree = expression(&token);
	print_tree(tree);



//	free_2d_array(&split);
//	free_token(token);
//	free_tree(tree);
	return (0);
}
