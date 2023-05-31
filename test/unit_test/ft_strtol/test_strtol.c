#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "./../../../libft/includes/ft_lib.h"

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

static int	test(const char *str, int test_no, bool expected_success)
{
	long	ft_ret, lib_ret;
	char	*ft_endptr, *lib_endptr;
	bool	ft_success, res_endptr;

	ft_success = ft_strtol(str, &ft_ret, &ft_endptr);
	lib_ret = strtol(str, &lib_endptr, 10);
	res_endptr = strcmp(ft_endptr, lib_endptr) == 0;

	printf("\n[TEST %02d] '%s'\n", test_no, str);
	printf(   "            num:%s  lib[%ld]\n", get_result_char(lib_ret == ft_ret), lib_ret);
	printf(   "                    ft_[%ld]\n", ft_ret);
	printf(   "            end:%s  lib[%s]\n", get_result_char(res_endptr), lib_endptr);
	printf(   "                    ft_[%s]\n", ft_endptr);
	printf(   "            suc:%s  ft_[%s]\n", get_result_char(expected_success == ft_success), get_bool_char(ft_success));

	if (lib_ret == ft_ret && res_endptr && expected_success == ft_success)
		return (1);
	return (0);
}

int	main(void)
{
	int	ok_cnt;
	int	test_no;

	printf("LONG_MAX: \nLONG_MIN: %ld%ld\n", LONG_MAX, LONG_MIN);
	ok_cnt = 0;
	test_no = 0;

	printf("===== convert success =====\n");
	ok_cnt += test("0", ++test_no, true);
	ok_cnt += test("1", ++test_no, true);
	ok_cnt += test("-1", ++test_no, true);
	ok_cnt += test("2147483647", ++test_no, true);
	ok_cnt += test("-2147483648", ++test_no, true);
	ok_cnt += test("9223372036854775807", ++test_no, true);
	ok_cnt += test("-9223372036854775808", ++test_no, true);
	ok_cnt += test("0000000000", ++test_no, true);
	ok_cnt += test("+0000000000", ++test_no, true);
	ok_cnt += test("-000000100", ++test_no, true);
	ok_cnt += test("   -123", ++test_no, true);
	ok_cnt += test(" +123", ++test_no, true);

	printf("\n\n===== convert success (must check endptr) =====\n");
	ok_cnt += test(" +123 ", ++test_no, true);
	ok_cnt += test("   -123.45", ++test_no, true);
	ok_cnt += test(" 123 000abc", ++test_no, true);


	printf("\n\n===== convert failure (non numeric, over/under flow) =====\n");
	ok_cnt += test("   - 123", ++test_no, false);
	ok_cnt += test(" +-123", ++test_no, false);
	ok_cnt += test("9223372036854775808", ++test_no, false);
	ok_cnt += test("9223372036854775809", ++test_no, false);
	ok_cnt += test("9223372036854775809", ++test_no, false);
	ok_cnt += test("9223372036854775810", ++test_no, false);
	ok_cnt += test("9223372036854775811", ++test_no, false);
	ok_cnt += test("9223372036854775812", ++test_no, false);
	ok_cnt += test("9223372036854775899", ++test_no, false);
	ok_cnt += test("92233720368547758080", ++test_no, false);
	ok_cnt += test("92233720368547758081", ++test_no, false);
	ok_cnt += test("92233720368547758082", ++test_no, false);
	ok_cnt += test("92233720368547758080123", ++test_no, false);
	ok_cnt += test("-9223372036854775809", ++test_no, false);
	ok_cnt += test("92233720368547758080123 ", ++test_no, false);
	ok_cnt += test("92233720368547758080123abc", ++test_no, false);
	ok_cnt += test("9223372036854775808012399999999999999999999999999999999999999999999abc", ++test_no, false);

	printf("############################################\n");
	printf(" TEST RESULT :: OK %d/ ALL %d     %s\n", ok_cnt, test_no, test_no == ok_cnt ? "\x1b[32mALL OK :)\x1b[0m" : "\x1b[31mNG :X\x1b[0m");
	printf("############################################\n\n");

	if (test_no != ok_cnt)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}