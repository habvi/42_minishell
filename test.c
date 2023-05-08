#include <stdio.h>
#include "test1.c"

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (1);

	printf("hello, minishell!!\n");
	print_str_x5(argv[1]);

	return (0);
}
