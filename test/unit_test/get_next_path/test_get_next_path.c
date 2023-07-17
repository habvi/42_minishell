#include <stdio.h>
#include <stdlib.h>
#include "ft_string.h"
#include "minishell.h"

int	test_get_next_path(char *path_list, char **expected, int test_no)
{
	char	*path;
	char 	*paths_src = ft_strjoin(path_list, ":");
	char	*ptr;
	bool	is_ok;
	size_t	i;

	is_ok = true;
	i = 0;
	ptr = paths_src;
	printf("No. %d\n", test_no);

	printf("  split   :[");
	while (*paths_src)
	{
		path = get_next_path(&paths_src);

		if (is_ok)
		{
			is_ok &= ft_streq(path, expected[i]);
			i++;
		}
		printf("%s", path);
		free(path);
		if (*paths_src)
			printf(",");
	}
	printf("]\n");
	free(ptr);

	if (expected[i])
		is_ok = false;

	printf("  expected:[");
	while (*expected)
	{
		printf("%s", *expected);
		expected++;
		if (*expected)
			printf(",");
	}
	printf("]\n");
	printf("  RESULT:%s\n", is_ok ? "OK" : "NG");
	return (is_ok);
}

int	main(void)
{
	int	test_no;
	int	ok_cnt;

	test_no = 0;
	ok_cnt = 0;
	ok_cnt += test_get_next_path("/bin:/usr/bin", (char *[]){"/bin/", "/usr/bin/", NULL}, test_no++);
	ok_cnt += test_get_next_path("a:b:c", (char *[]){"a/", "b/", "c/", NULL}, test_no++);
	ok_cnt += test_get_next_path("a::b::c", (char *[]){"a/","","b/","","c/", NULL}, test_no++);
	ok_cnt += test_get_next_path(":a:b:c", (char *[]){"","a/","b/","c/", NULL}, test_no++);
	ok_cnt += test_get_next_path(":a", (char *[]){"","a/", NULL}, test_no++);
	ok_cnt += test_get_next_path("a", (char *[]){"a/", NULL}, test_no++);
	ok_cnt += test_get_next_path("a:", (char *[]){"a/","", NULL}, test_no++);
	ok_cnt += test_get_next_path("a::", (char *[]){"a/","","", NULL}, test_no++);
	ok_cnt += test_get_next_path("", (char *[]){"", NULL}, test_no++);
	ok_cnt += test_get_next_path(":", (char *[]){"","", NULL}, test_no++);
	ok_cnt += test_get_next_path("::", (char *[]){"","","", NULL}, test_no++);
	ok_cnt += test_get_next_path(":::", (char *[]){"","","","", NULL}, test_no++);

	printf("\n");
	printf("############################################\n");
	printf(" TEST RESULT :: OK %d/ ALL %d     %s\n", ok_cnt, test_no, test_no == ok_cnt ? "\x1b[32mALL OK :)\x1b[0m" : "\x1b[31mNG :X\x1b[0m");
	printf("############################################\n\n");

	if (test_no == ok_cnt)
		return (0);
	return (1);
}



























