#include <stdio.h>
#include <stdlib.h>
#include "ft_hash.h"
#include "ft_dprintf.h"

#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_YELLOW	"\x1b[33m"
#define COLOR_BLUE		"\x1b[34m"
#define COLOR_MAGENTA	"\x1b[35m"
#define COLOR_CYAN		"\x1b[36m"
#define COLOR_RESET		"\x1b[0m"

void	display_elem(void *content)
{
	t_elem	*elem;

	if (!content)
		return ;
	elem = content;
	ft_dprintf(STDERR_FILENO, "[%s, %s]", elem->key, elem->value);
}

static char *get_result_char(int res)
{
	if (res)
		return (COLOR_GREEN"OK"COLOR_RESET);
	return (COLOR_RED"NG"COLOR_RESET);
}

int	test_hash_value(char *key, uint64_t mod, uint64_t expected, int no)
{
	uint64_t	hash = generate_fnv_hash_64((const unsigned char *)key, mod);
	printf("[%02d] %s\n", no, get_result_char(hash == expected));
	printf("     key       :\"%s\"\n", key);
	printf("     hash      :%lu\n", hash);
	printf("     expected  :%lu\n", expected);

	if (hash != expected)
		return (0);
	return (1);
}

int	main(void)
{
	int	test_no = 0;
	int	ok = 0;
	{
		printf(" ===== hash value =====\n");

		ok += test_hash_value("example", 0, 0x44ec942469dbbb3d, ++test_no);
		ok += test_hash_value("abc", 0, 0xd8dcca186bafadcb, ++test_no);
		ok += test_hash_value("PATH", 0, 0x9751cc7e14924228, ++test_no);
		ok += test_hash_value("42tokyo", 0, 0x264eda1ad1daa90f, ++test_no);
		ok += test_hash_value("", 0, 0xcbf29ce484222325, ++test_no);
		printf("\n");
	}
	{
		printf(" ===== hash table =====\n");

		t_hash	*hash = create_hash_table(1);

		display_hash_table(hash, display_elem);
		printf("\n");
	}


	printf("############################################\n");
	printf(" TEST RESULT :: OK %d/ ALL %d     %s\n", ok, test_no, test_no == ok ? "\x1b[32mALL OK :)\x1b[0m" : "\x1b[31mNG :X\x1b[0m");
	printf("############################################\n\n");

	if (test_no != ok)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
