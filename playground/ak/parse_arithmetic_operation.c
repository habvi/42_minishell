#include "test.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage               : $ ./a.out \"numerical formula\"\n"
			   "available operators : +, -, *, /, (, )\n");
		return (1);
	}
	printf("%s\n", argv[1]);
	return (0);
}