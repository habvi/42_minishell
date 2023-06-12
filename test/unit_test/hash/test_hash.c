#include <stdio.h>
#include <stdlib.h>
#include "ft_hash.h"
#include "ft_dprintf.h"
#include "ft_string.h"

#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_RESET		"\x1b[0m"

void	display_elem(void *content)
{
	t_elem	*elem;

	if (!content)
		return ;
	elem = content;
	ft_dprintf(STDERR_FILENO, "[\"%s\", \"%s\"]", \
	elem->key, (char *)elem->content);
}

void	display_table_info(t_hash *hash)
{
	printf("table size:%zu\n", hash->table_size);
	printf("key count :%zu\n", hash->key_count);
	display_hash_table(hash, display_elem);
}

static char *get_result_char(int res)
{
	if (res)
		return (COLOR_GREEN"OK"COLOR_RESET);
	return (COLOR_RED"NG"COLOR_RESET);
}

int	test_hash_value(char *key, uint64_t mod, uint64_t expected, int no)
{
	uint64_t	hash =  gen_fnv_hash((const unsigned char *)key, mod);
	printf("[%02d] %s\n", no, get_result_char(hash == expected));
	printf("     key       :\"%s\"\n", key);
	printf("     hash      :%lu\n", hash);
	printf("     expected  :%lu\n", expected);

	if (hash != expected)
		return (0);
	return (1);
}

void	del_elem_content_test(void *content)
{
	char	*value;

	value = (char *)content;
	free(value);
}

static void	set_to_table_by_allocated_strs(t_hash *hash, const char *s1, const char *s2)
{
	char	*s1_dup = NULL;
	char	*s2_dup = NULL;

	if (s1)
		s1_dup = ft_strdup(s1);
	if (s2)
		s2_dup = ft_strdup(s2);
	set_to_table(hash, s1_dup, s2_dup, del_elem_content_test);
}

int	main(void)
{
	int	test_no = 0;
	int	ok = 0;
	{
		printf(" ========== hash value ==========\n");

		ok += test_hash_value("example", 0, 0x44ec942469dbbb3d, ++test_no);
		ok += test_hash_value("abc", 0, 0xd8dcca186bafadcb, ++test_no);
		ok += test_hash_value("PATH", 0, 0x9751cc7e14924228, ++test_no);
		ok += test_hash_value("42tokyo", 0, 0x264eda1ad1daa90f, ++test_no);
		ok += test_hash_value("", 0, 0xcbf29ce484222325, ++test_no);
		printf("\n\n");
	}
	{
		printf(" ========== hash table (except rehash) ==========\n");

		t_hash	*hash = create_hash_table(100);
		display_hash_table(hash, display_elem);

		set_to_table_by_allocated_strs(hash, "test_key", "test_value");
		set_to_table_by_allocated_strs(hash, "pien", ";p");
		set_to_table_by_allocated_strs(hash, "PATH", "/bin:/usr/bin:etc");
		display_table_info(hash);

		set_to_table_by_allocated_strs(hash, "empty string", "");
		display_table_info(hash);

		set_to_table_by_allocated_strs(hash, "empty value", NULL);
		display_table_info(hash);

		set_to_table_by_allocated_strs(hash, "PATHa", "/bin:/usr/bin:etc");
		set_to_table_by_allocated_strs(hash, "PATH1", "/bin:/usr/bin:etc1");
		display_table_info(hash);

		set_to_table_by_allocated_strs(hash, "abc", "abc1");
		set_to_table_by_allocated_strs(hash, "abc", "abc2");
		set_to_table_by_allocated_strs(hash, "abc", "abc3");
		set_to_table_by_allocated_strs(hash, "abc", "abc4");
		set_to_table_by_allocated_strs(hash, "abc", "abc5");
		display_table_info(hash);

		clear_hash_table(&hash, del_elem_content_test);

		printf("\n\n");
	}
	{
		printf(" ===== hash table (use rehash) =====\n");

		t_hash	*hash = create_hash_table(1);
		display_table_info(hash);
		clear_hash_table(&hash, del_elem_content_test);
		printf("\n\n");
	}

	printf("\n############################################\n");
	printf(" TEST RESULT :: OK %d / ALL %d     %s\n", \
			ok, test_no, test_no == ok ? COLOR_GREEN"ALL OK :)"COLOR_RESET : COLOR_RED"NG :X"COLOR_RESET);
	printf("############################################\n\n");

	if (test_no != ok)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
