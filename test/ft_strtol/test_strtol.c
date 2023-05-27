#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <sys/errno.h>
#include "./../../libft/includes/ft_lib.h"
#include "./../../libft/includes/ft_ascii.h"

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

static char *get_result_char(int res, bool skip)
{
	if (skip)
		return (COLOR_YELLOW"SKIP"COLOR_RESET);
	if (res)
		return (COLOR_GREEN"OK"COLOR_RESET);
	return (COLOR_RED"NG"COLOR_RESET);
}

static int	test(const char *str, bool allow_tail_space, int test_no)
{
	long	ft_ret, lib_ret;
	bool	ft_success, lib_success;
	char	*endptr;

	ft_success = ft_strtol(str, &ft_ret, allow_tail_space);

	lib_ret = strtol(str, &endptr, 10);
	lib_success = strlen(endptr) == 0;

	printf("\n[TEST %02d] '%s'\n", test_no, str);
	printf(   "            num:%s  lib[%ld]\n", get_result_char(lib_ret == ft_ret, false), lib_ret);
	printf(   "                    ft_[%ld]\n", ft_ret);
	printf(   "            end:%s  lib[%s]\n", get_result_char(lib_success == ft_success, allow_tail_space), get_bool_char(lib_success));
	printf(   "                    ft_[%s]\n", get_bool_char(ft_success));

	if (allow_tail_space && lib_ret == ft_ret)
		return (1);
	if (lib_ret == ft_ret && lib_success == ft_success)
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
	ok_cnt += test("0", false, ++test_no);
	ok_cnt += test("1", false, ++test_no);
	ok_cnt += test("-1", false, ++test_no);
	ok_cnt += test("2147483647", false, ++test_no);
	ok_cnt += test("-2147483648", false, ++test_no);
	ok_cnt += test("9223372036854775807", false, ++test_no);
	ok_cnt += test("-9223372036854775808", false, ++test_no);
	ok_cnt += test("0000000000", false, ++test_no);
	ok_cnt += test("+0000000000", false, ++test_no);
	ok_cnt += test("-000000100", false, ++test_no);
	ok_cnt += test("   -123", false, ++test_no);
	ok_cnt += test(" +123", false, ++test_no);

	printf("\n\n===== convert failure (Not allowed tail space) =====\n");
	ok_cnt += test("   - 123", false, ++test_no);
	ok_cnt += test(" +-123", false, ++test_no);
	ok_cnt += test(" +123 ", false, ++test_no);
	ok_cnt += test("   -123.45", false, ++test_no);
	ok_cnt += test("9223372036854775808", false, ++test_no); // lib is success??
	ok_cnt += test("-9223372036854775809", false, ++test_no); // lib is success??

	printf("\n\n===== convert success (Allowed tail space) =====\n");
	ok_cnt += test("   0   ", true, ++test_no);
	ok_cnt += test("1	", true, ++test_no);
	ok_cnt += test("-1\t  ", true, ++test_no);
	ok_cnt += test("2147483647  ", true, ++test_no);
	ok_cnt += test("-2147483648    ", true, ++test_no);
	ok_cnt += test("9223372036854775807  ", true, ++test_no);
	ok_cnt += test("-9223372036854775808  ", true, ++test_no);


	printf("############################################\n");
	printf(" TEST RESULT :: OK %d/ ALL %d     %s\n", ok_cnt, test_no, test_no == ok_cnt ? "\x1b[32mALL OK :)\x1b[0m" : "\x1b[31mNG :X\x1b[0m");
	printf("############################################\n\n");
	return (0);
}