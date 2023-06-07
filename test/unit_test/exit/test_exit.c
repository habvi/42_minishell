#include <stdlib.h>
#include <stdio.h>
#include "ft_lib.h"
#include "ms_builtin.h"

#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_YELLOW	"\x1b[33m"
#define COLOR_BLUE		"\x1b[34m"
#define COLOR_MAGENTA	"\x1b[35m"
#define COLOR_CYAN		"\x1b[36m"
#define COLOR_RESET		"\x1b[0m"

static char *get_result_char(int res)
{
	if (res)
		return (COLOR_GREEN"OK"COLOR_RESET);
	return (COLOR_RED"NG"COLOR_RESET);
}

static void	print_cmds(char *const *cmds)
{
	size_t i = 0;

	printf("cmds:[\n");
	while (cmds[i])
	{
		printf("%s", cmds[i]);
		i++;
		if (cmds[i])
			printf(", ");
	}
	printf("]\n");
}

static int	test(char *const *cmds, int expected_status, int test_no)
{
	int	ft_ret = ft_exit(cmds, NULL);

	printf("\n[TEST %02d] ", test_no);
	print_cmds(cmds);
	printf(   "           result:%s  exp[%d]\n", get_result_char(ft_ret == expected_status), expected_status);
	printf(   "                      ft_[%d]\n", ft_ret);

	if (ft_ret == expected_status)
		return (1);
	return (0);
}

int	main(void)
{
	int	ok_cnt;
	int	test_no;

	ok_cnt = 0;
	test_no = 0;

	printf("===== success =====\n");
	char *const cmds1[10] = {"exit", NULL};
	ok_cnt += test(cmds1, 0, ++test_no); // actually KO

	char *const cmds2[10] = {"exit", "1"};
	ok_cnt += test(cmds2, 1, ++test_no);

	char *const cmds3[10] = {"exit", "42"};
	ok_cnt += test(cmds3, 42, ++test_no);

	char *const cmds4[10] = {"exit", "-1"};
	ok_cnt += test(cmds4, 255, ++test_no);

	char *const cmds5[10] = {"exit", "2147483647"};
	ok_cnt += test(cmds5, 255, ++test_no);

	char *const cmds6[10] = {"exit", "-2147483648"};
	ok_cnt += test(cmds6, 0, ++test_no);

	char *const cmds7[10] = {"exit", "9223372036854775807"};
	ok_cnt += test(cmds7, 255, ++test_no);

	char *const cmds8[10] = {"exit", "-9223372036854775808"};
	ok_cnt += test(cmds8, 0, ++test_no);

	char *const cmds9[10] = {"exit", "+0000000001"};
	ok_cnt += test(cmds9, 1, ++test_no);

	char *const cmds10[10] = {"exit", "+000000000"};
	ok_cnt += test(cmds10, 0, ++test_no);


	printf("\n===== faulure =====\n");

	char *const cmds21[10] = {"exit", "9223372036854775808"};
	ok_cnt += test(cmds21, 2, ++test_no);

	char *const cmds22[10] = {"exit", "-9223372036854775809"};
	ok_cnt += test(cmds22, 2, ++test_no);

	char *const cmds23[10] = {"exit", "a"};
	ok_cnt += test(cmds23, 2, ++test_no);

	char *const cmds24[10] = {"exit", "a", "a"};
	ok_cnt += test(cmds24, 2, ++test_no);

	char *const cmds25[10] = {"exit", "1", "a"};
	ok_cnt += test(cmds25, 1, ++test_no);

	char *const cmds26[10] = {"exit", "+-1"};
	ok_cnt += test(cmds26, 2, ++test_no);

	char *const cmds27[10] = {"exit", "", "5"};
	ok_cnt += test(cmds27, 2, ++test_no);

	char *const cmds28[10] = {"exit", "5", ""};
	ok_cnt += test(cmds28, 1, ++test_no);

	printf("############################################\n");
	printf(" TEST RESULT :: OK %d/ ALL %d     %s\n", ok_cnt, test_no, test_no == ok_cnt ? "\x1b[32mALL OK :)\x1b[0m" : "\x1b[31mNG :X\x1b[0m");
	printf("############################################\n\n");

	if (test_no != ok_cnt)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
