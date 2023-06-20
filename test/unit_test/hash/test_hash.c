#include <stdio.h>
#include <stdlib.h>
#include "ft_hash.h"
#include "ft_dprintf.h"
#include "ft_string.h"

#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_RESET		"\x1b[0m"

static void	display_elem(void *content)
{
	t_elem	*elem;

	if (!content)
		return ;
	elem = content;
	ft_dprintf(STDERR_FILENO, "[\"%s\", \"%s\"]", \
	elem->key, (char *)elem->value);
}

static void	display_table_info(t_hash *hash)
{
	printf("table size:%zu\n", hash->table_size);
	printf("key count :%zu\n", hash->key_count);
	hs_display(hash, display_elem);
}

static char *get_result_char(int res)
{
	if (res)
		return (COLOR_GREEN"OK"COLOR_RESET);
	return (COLOR_RED"NG"COLOR_RESET);
}

static int	test_hash_value(char *key, uint64_t mod, uint64_t expected, int no)
{
	uint64_t	hash =  hs_gen_fnv((const unsigned char *)key, mod);
	printf("[%02d] %s\n", no, get_result_char(hash == expected));
	printf("     key       :\"%s\"\n", key);
	printf("     hash      :%lu\n", hash);
	printf("     expected  :%lu\n", expected);

	if (hash != expected)
		return (0);
	return (1);
}

static int	test_get_value(t_hash *hash, char *key, char *expected_val, int no)
{
	char	*value = (char *)hs_get_value(hash, key);
	int		res;

	if (!value && !expected_val)
		res =  true;
	else
		res = ft_streq(value, expected_val);
	printf("[%02d] %s\n", no, get_result_char(res));
	printf("     key       :\"%s\"\n", key);
	printf("     value     :\"%s\"\n", value);
	printf("     expected  :\"%s\"\n", expected_val);

	if (!res)
		return (0);
	return (1);
}

static void	del_elem_content_test(void *content)
{
	char	*value;

	value = (char *)content;
	free(value);
}

static void	test_hs_delete_key(t_hash *hash, const char *key)
{
	hs_delete_key(hash, key);
}

static void	set_to_table_by_allocated_strs(t_hash *hash, const char *s1, const char *s2)
{
	char	*s1_dup = NULL;
	char	*s2_dup = NULL;

	if (s1)
		s1_dup = ft_strdup(s1);
	if (s2)
		s2_dup = ft_strdup(s2);
	hs_set_key(hash, s1_dup, s2_dup);
}

int	main(void)
{
	int	test_no = 0;
	int	ok = 0;
	{
		printf("\n ========== hash value ==========\n");

		ok += test_hash_value("example", 0, 0x44ec942469dbbb3d, ++test_no);
		ok += test_hash_value("abc", 0, 0xd8dcca186bafadcb, ++test_no);
		ok += test_hash_value("PATH", 0, 0x9751cc7e14924228, ++test_no);
		ok += test_hash_value("42tokyo", 0, 0x264eda1ad1daa90f, ++test_no);
		ok += test_hash_value("", 0, 0xcbf29ce484222325, ++test_no);
		printf("\n\n");
	}
	{
		printf("\n ========== hash table (except rehash) ==========\n");

		t_hash	*hash = hs_create_table(100, del_elem_content_test);
		hs_display(hash, display_elem);

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

		hs_clear(&hash);

		printf("\n\n");
	}
	{
		printf("\n ===== hash table (use rehash) =====\n");

		t_hash	*hash = hs_create_table(1, del_elem_content_test);
		display_table_info(hash);
		set_to_table_by_allocated_strs(hash, "abc", "value of abc");
		set_to_table_by_allocated_strs(hash, "abc1", "value of abc1");
		set_to_table_by_allocated_strs(hash, "abc1", "value of abc2");
		set_to_table_by_allocated_strs(hash, "ABC", "value of ABC");
		set_to_table_by_allocated_strs(hash, "ABCD", "value of ABC");
		set_to_table_by_allocated_strs(hash, "ABCDE", "value of ABC");
		display_table_info(hash);
		hs_clear(&hash);
		printf("\n\n");
	}
	{
		printf("\n ===== find key =====\n");

		t_hash	*hash = hs_create_table(100, del_elem_content_test);

		set_to_table_by_allocated_strs(hash, "abc", "value of abc");
		set_to_table_by_allocated_strs(hash, "abc1", "value of abc1");
		set_to_table_by_allocated_strs(hash, "abc1", "value of abc2");
		set_to_table_by_allocated_strs(hash, "ABC", "value of ABC");
		set_to_table_by_allocated_strs(hash, "12345", "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
		set_to_table_by_allocated_strs(hash, "12345", "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
		set_to_table_by_allocated_strs(hash, "12345", "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
		set_to_table_by_allocated_strs(hash, "test", "");
		set_to_table_by_allocated_strs(hash, "null", NULL);
		display_table_info(hash);

		printf("\n   ----- key exists in the table -----\n");
		ok += test_get_value(hash, "abc", "value of abc", ++test_no);
		ok += test_get_value(hash, "abc1", "value of abc2", ++test_no);
		ok += test_get_value(hash, "test", "", ++test_no);
		ok += test_get_value(hash, "null", NULL, ++test_no);
		ok += test_get_value(hash, "12345", "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no);

		printf("\n   ----- key not found -----\n");
		ok += test_get_value(hash, "nothing", NULL, ++test_no);
		ok += test_get_value(hash, "", NULL, ++test_no);
		ok += test_get_value(hash, "abC", NULL, ++test_no);
		ok += test_get_value(hash, "abc2", NULL, ++test_no);
		ok += test_get_value(hash, "", NULL, ++test_no);
		ok += test_get_value(hash,  "42Tokyo", NULL, ++test_no);

		printf("\n   ----- after del key -----\n");
		display_table_info(hash);
		test_hs_delete_key(hash, "abc1");
		display_table_info(hash);
		test_hs_delete_key(hash, "12345");
		display_table_info(hash);
		test_hs_delete_key(hash, "not_exist_key");
		display_table_info(hash);
		test_hs_delete_key(hash, "not_exist_key");
		display_table_info(hash);

		hs_clear(&hash);
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
