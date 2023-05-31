#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "ms_builtin.h"

#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_YELLOW	"\x1b[33m"
#define COLOR_BLUE		"\x1b[34m"
#define COLOR_MAGENTA	"\x1b[35m"
#define COLOR_CYAN		"\x1b[36m"
#define COLOR_RESET		"\x1b[0m"

static char	*get_bool_char(bool b)
{
	if (b)
		return ("true");
	return ("false");
}

static char *get_result_char(int res)
{
	if (res)
		return (COLOR_GREEN"OK"COLOR_RESET);
	return (COLOR_RED"NG"COLOR_RESET);
}

static int	test(const char *str, long expected_val, bool expected_bool, int test_no)
{
	long	res_val;
	bool	ret_bool;

	ret_bool = ft_legal_number(str, &res_val);

	printf("\n[TEST %02d] '%s'\n", test_no, str);
	printf(   "            %s : val=[%ld]\n", get_result_char(res_val == expected_val), res_val);
	printf(   "            %s : ret=[%s]\n", get_result_char(ret_bool == expected_bool), get_bool_char(ret_bool));

	if (ret_bool == expected_bool && res_val == expected_val)
		return (1);
	return (0);
}

int	main(void)
{
	int	ok_cnt;
	int	test_no;

	ok_cnt = 0;
	test_no = 0;

	printf("===== convert success =====\n");
	ok_cnt += test(" 0 ", 0, true, ++test_no);
	ok_cnt += test("    9223372036854775807   ", LONG_MAX, true, ++test_no);
	ok_cnt += test("   -9223372036854775808 ", LONG_MIN, true, ++test_no);
	ok_cnt += test("  \n     \r +123\t\t\t\t\t    \t", 123, true, ++test_no);

	printf("\n\n===== convert failure =====\n");
	ok_cnt += test(" --0 ", 0, false, ++test_no);
	ok_cnt += test(" 0 \n ", 0, false, ++test_no);
	ok_cnt += test(" 0  aaa  ", 0, false, ++test_no);
	ok_cnt += test(" \a 0 ", 0, false, ++test_no);
	ok_cnt += test(" 123   \v ", 0, false, ++test_no);

	printf("############################################\n");
	printf(" TEST RESULT :: OK %d/ ALL %d     %s\n", ok_cnt, test_no, test_no == ok_cnt ? "\x1b[32mALL OK :)\x1b[0m" : "\x1b[31mNG :X\x1b[0m");
	printf("############################################\n\n");

	if (test_no != ok_cnt)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
