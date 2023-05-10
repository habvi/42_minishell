#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// expected a -> A
// actual   a -> `
char	*str_toupper(char *str)
{
	char	*ret;
	size_t	i;

	ret = strdup(str);
	i = 0;
	while (ret && ret[i])
	{
		if (ret[i] == 'a')	// BUG
			ret[i]--;
		else if (islower(ret[i]))
			ret[i] = toupper(ret[i]);
		i++;
	}
	return (ret);
}

// if argc > 3, memory leak occurred
int	main(int argc, char **argv)
{
	char	*print_str;

	if (argc == 1)
		return (1);

	print_str = str_toupper(argv[1]); // malloc

	if (argc > 2)
		return (1);

	printf("%s\n", print_str);
	free(print_str);
	return (0);
}
