#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "./../../../libft/includes/ft_string.h"

#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_YELLOW	"\x1b[33m"
#define COLOR_BLUE		"\x1b[34m"
#define COLOR_MAGENTA	"\x1b[35m"
#define COLOR_CYAN		"\x1b[36m"
#define COLOR_RESET		"\x1b[0m"

static int	test(char *s1, unsigned int start, char *s2, int test_no)
{
	char	*new_s = ft_substr_tail(s1, start);
	bool	result = ft_streq(new_s, s2);
	printf(" [TEST %02d] ret = %s, %s\n", \
	test_no, \
	new_s, \
	result ? COLOR_GREEN"OK"COLOR_RESET : COLOR_RED"NG"COLOR_RESET);

	printf("   s1:[%s] (%d to tail)\n", s1, start);
	printf("   s2:[%s]\n", s2);
	printf("------------------------------\n");

	free(new_s);
	if (result)
		return (1);
	return (0);
}

int	main(void)
{
	int	ok_cnt = 0;
	int	test_no = 0;

	ok_cnt += test("", 0, "", ++test_no);
	ok_cnt += test("", 5, "", ++test_no);
	ok_cnt += test("abcdefg", 0, "abcdefg", ++test_no);
	ok_cnt += test("abcdefg", 3, "defg", ++test_no);
	ok_cnt += test("abcdefg", 6, "g", ++test_no);
	ok_cnt += test("abcdefg", 7, "", ++test_no);
	ok_cnt += test("abcdefg", 15, "", ++test_no);
	ok_cnt += test(NULL, 0, NULL, ++test_no);
	ok_cnt += test(NULL, 10, NULL, ++test_no);

	printf("\n#############################\n");
	printf("   RESULT: ok_cnt %d/ all %d    %s\n", ok_cnt, test_no, ok_cnt == test_no ? COLOR_GREEN"OK"COLOR_RESET : COLOR_RED"NG"COLOR_RESET);
	printf("#############################\n");

	if (test_no != ok_cnt)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
