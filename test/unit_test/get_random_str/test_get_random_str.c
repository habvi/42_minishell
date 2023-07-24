#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "minishell.h"
#include "ft_mem.h"
#include "ft_string.h"

#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_YELLOW	"\x1b[33m"
#define COLOR_BLUE		"\x1b[34m"
#define COLOR_MAGENTA	"\x1b[35m"
#define COLOR_CYAN		"\x1b[36m"
#define COLOR_RESET		"\x1b[0m"

static bool	is_alnum_all(const size_t size, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && isalnum(str[i]))
		i++;
	return (i == size);
}

static int	test(const size_t size, int test_no)
{
	char	*str1 = get_random_str(size);
	char	*str2 = get_random_str(size);
	bool	result;

	result = true;
	result &= (size == strlen(str1));
	result &= (size == strlen(str2));
	result &= is_alnum_all(size, str1);
	result &= is_alnum_all(size, str2);
	result &= !ft_streq(str1, str2);

	printf(" [TEST %02d]\n ret=[%s]\n ret=[%s]\n %s\n", 
	test_no, 
	str1, 
	str2, 
	result ? COLOR_GREEN"OK"COLOR_RESET : COLOR_RED"NG"COLOR_RESET);
	printf("------------------------------\n");

	ft_free((void **)&str1);
	ft_free((void **)&str2);
	if (result)
		return (1);
	return (0);
}

int	main(void)
{
	int		ok_cnt = 0;
	int		test_no = 0;

	size_t	i;

	i = 0;
	while (i < 10)
	{
		ok_cnt += test(50, ++test_no);
		i++;
	}

	printf("\n#############################\n");
	printf("   RESULT: ok_cnt %d/ all %d    %s\n", ok_cnt, test_no, ok_cnt == test_no ? COLOR_GREEN"OK"COLOR_RESET : COLOR_RED"NG"COLOR_RESET);
	printf("#############################\n");

	if (test_no != ok_cnt)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
