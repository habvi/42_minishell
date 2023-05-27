#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <sys/errno.h>
#include "./../../libft/includes/ft_lib.h"
#include "./../../libft/includes/ft_ascii.h"

static char	*get_bool_char(bool b)
{
	if (b)
		return ("true");
	return ("false");
}

static int	test(const char *str, int test_no)
{
	long	ft_ret, lib_ret;
	bool	ft_success, lib_success;
	char	*endptr;
	int		lib_errno;

	ft_success = ft_strtol(str, &ft_ret);

	errno = 0;
	lib_ret = strtol(str, &endptr, 10);
	lib_errno = errno;
	lib_success = strlen(endptr) == 0;

	printf("\n[TEST %02d] %s\n", test_no, str);
	printf(   "            num:%s  lib[%ld]\n", lib_ret == ft_ret ? "\x1b[32mOK\x1b[0m" : "\x1b[31mNG\x1b[0m", lib_ret);
	printf(   "                    ft_[%ld]\n", ft_ret);
	printf(   "            end:%s  lib[%s], errno:%d\n", lib_success == ft_success ? "\x1b[32mOK\x1b[0m" : "\x1b[31mNG\x1b[0m", get_bool_char(lib_success), lib_errno);
	printf(   "                    ft_[%s]\n", get_bool_char(ft_success));
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
	ok_cnt += test("0", ++test_no);
	ok_cnt += test("1", ++test_no);
	ok_cnt += test("-1", ++test_no);
	ok_cnt += test("2147483647", ++test_no);
	ok_cnt += test("-2147483648", ++test_no);
	ok_cnt += test("9223372036854775807", ++test_no);
	ok_cnt += test("-9223372036854775808", ++test_no);
	ok_cnt += test("0000000000", ++test_no);
	ok_cnt += test("+0000000000", ++test_no);
	ok_cnt += test("-000000100", ++test_no);
	ok_cnt += test("   -123", ++test_no);
	ok_cnt += test(" +123", ++test_no);

	printf("\n===== convert failure =====\n");
	ok_cnt += test("   - 123", ++test_no);
	ok_cnt += test(" +-123", ++test_no);
	ok_cnt += test(" +123 ", ++test_no);
	ok_cnt += test("   -123.45", ++test_no);
	ok_cnt += test("9223372036854775808", ++test_no); // lib is success, but errno=34(ERANGE)
	ok_cnt += test("-9223372036854775809", ++test_no);

	printf("############################################\n");
	printf(" TEST RESULT :: OK %d/ ALL %d     %s\n", ok_cnt, test_no, test_no == ok_cnt ? "\x1b[32mALL OK :)\x1b[0m" : "\x1b[31mNG :X\x1b[0m");
	printf("############################################\n\n");
	return (0);
}