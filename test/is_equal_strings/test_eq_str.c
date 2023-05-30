#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "./../../libft/includes/ft_string.h"

#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_YELLOW	"\x1b[33m"
#define COLOR_BLUE		"\x1b[34m"
#define COLOR_MAGENTA	"\x1b[35m"
#define COLOR_CYAN		"\x1b[36m"
#define COLOR_RESET		"\x1b[0m"

static char	*get_bool_str(bool b)
{
	if (b)
		return ("true");
	return ("false");
}

static int	test(char *s1, char *s2, int test_no, bool expected)
{
	bool	ret = is_equal_strings(s1, s2);
	printf(" [TEST %02d] ret = %s, %s\n", \
	test_no, get_bool_str(ret), \
	ret == expected ? COLOR_GREEN"OK"COLOR_RESET : COLOR_RED"NG"COLOR_RESET);

	printf("   s1:[%s]\n", s1);
	printf("   s2:[%s]\n", s2);
	printf("------------------------------\n");
	if (ret == expected)
		return (1);
	return (0);
}

int	main(void)
{
	int	ok_cnt = 0;
	int	test_no = 0;

	printf("=============== true expected ===============\n");
	ok_cnt += test("a", "a", ++test_no, true);
	ok_cnt += test("abc", "abc", ++test_no, true);
	ok_cnt += test("Abc123 ", "Abc123 ", ++test_no, true);
	ok_cnt += test("", "", ++test_no, true);
	ok_cnt += test("abc\0def", "abc\0DEF", ++test_no, true);

	printf("\n\n=============== false  expected ===============\n\n");
	ok_cnt += test(NULL, NULL, ++test_no, false);
	ok_cnt += test(NULL, "", ++test_no, false);
	ok_cnt += test("a", NULL, ++test_no, false);
	ok_cnt += test("abc", "ABC", ++test_no, false);
	ok_cnt += test("abc", "abcd", ++test_no, false);
	ok_cnt += test("abcd", "abc", ++test_no, false);
	ok_cnt += test("abcdefg", "", ++test_no, false);
	ok_cnt += test("", "            ", ++test_no, false);
	ok_cnt += test("123", "123123", ++test_no, false);

	printf("\n#############################\n");
	printf("   RESULT: ok_cnt %d/ all %d    %s\n", ok_cnt, test_no, ok_cnt == test_no ? COLOR_GREEN"OK"COLOR_RESET : COLOR_RED"NG"COLOR_RESET);
	printf("#############################\n");

	if (test_no != ok_cnt)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
