#include "test.h"

static void	print_split(char **split)
{
	size_t	i;

	i = 0;
	printf("%-12s:[", "split");
	while (split && split[i])
	{
		printf("%s", split[i]);
		i++;
		if (split[i])
			printf(", ");
	}
	printf("]\n");
}

int	main(int argc, char **argv)
{
	char	**split;
	t_token	*token;
	t_tree	*tree;

	if (argc != 2)
	{
		printf("usage               : $ ./a.out \"numerical formula\"\n"
			   "available operators : +, -, *, /, (, )\n");
		return (1);
	}
	split = ft_split(argv[1], ' ');
	print_split(split);

	token = tokenize(split);
	print_token(token);

	tree = expression(&token);

//	printf("\n");
//	print_tree_node(tree, 0, "root");
//	print_tree_node(tree->lhs, 1, "root->left");
//	print_tree_node(tree->rhs, 1, "root->right");
//
//	if (tree->lhs)
//	{
//		print_tree_node(tree->lhs->lhs, 2, "root->left->left");
//		print_tree_node(tree->lhs->rhs, 2, "root->left->right");
//	}
//
//	if (tree->rhs)
//	{
//		print_tree_node(tree->rhs->lhs, 2, "root->right->left");
//		print_tree_node(tree->rhs->rhs, 2, "root->right->right");
//	}

	print_tree(tree);

//	free_2d_array(&split);
//	free_token(token);
//	free_tree(tree);
	return (0);
}
