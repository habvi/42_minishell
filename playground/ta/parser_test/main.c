#include "test.h"

static void	print_split(char **split)
{
	size_t	i;

	i = 0;
	printf("split:[");
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

	free_token(token);
	free_2d_array(&split);
	return (0);
}
