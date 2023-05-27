#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "./../../libft/includes/ft_string.h"

static char	*get_bool_str(bool b)
{
	if (b)
		return ("true");
	return ("false");
}

static void	test(char *s1, char *s2)
{
	bool	ret = is_equal_strings(s1, s2);
	printf(" [%s]==[%s] : %s\n", s1, s2, get_bool_str(ret));
}

int	main(void)
{
	printf("=== true ===\n");
	test("a", "a");
	test("abc", "abc");
	test("Abc123 ", "Abc123 ");
	test("", "");
	test("abc\0def", "abc\0DEF");

	printf("\n=== false ===\n");
	test(NULL, NULL);
	test(NULL, "");
	test("a", NULL);
	test("abc", "ABC");
	test("abc", "abcd");
	test("abcdefg", "");

	return (0);
}
