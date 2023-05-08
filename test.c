#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (1);

	printf("minishell...?\n");
	printf("%s\n", argv[1]);
	printf("minishell!!\n");
	return (0);
}
