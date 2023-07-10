#include <stdio.h>
#include "ft_string.h"

void	test(char *s, char *set)
{
	char	*ans = ft_find_set_in_str(s, set);
	printf("s:[%s], set:[%s], ans:[%s]\n", s, set, ans);
}

int	main(void)
{
	test("aa", "a");
	test("abc123", "123");
	test("       ", "  ");
	test("a   b   c", "c");
	test("a   b   c", "");
	test("'''''\"''''", "\"");
	test("'''''''''", "\"");
	return (0);
}
