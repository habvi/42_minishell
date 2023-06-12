#include <stdlib.h>
#include "ft_mem.h"
#include "ft_string.h"

static size_t	count_words(char const *head, char c)
{
	char const	*left = head;
	char const	*right = head;
	size_t		words;

	words = 0;
	while (*right != '\0')
	{
		while (*right == c)
		{
			left++;
			right++;
		}
		while (*right != '\0' && *right != c)
			right++;
		if (left != right)
		{
			words++;
			left = right;
		}
	}
	return (words);
}

static bool	set_split_str(char const *head, char c, char **split_strs)
{
	char const	*left = head;
	char const	*right = head;
	size_t		i;

	i = 0;
	while (*right != '\0')
	{
		while (*right == c)
		{
			left++;
			right++;
		}
		while (*right != '\0' && *right != c)
			right++;
		if (left != right)
		{
			split_strs[i] = ft_strndup(left, right - left);
			if (split_strs[i] == NULL)
				return (false);
			i++;
			left = right;
		}
	}
	return (true);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**split_strs;

	if (s == NULL)
		return (NULL);
	len = count_words(s, c);
	split_strs = (char **)malloc(sizeof(char *) * (len + 1));
	if (split_strs == NULL)
		return (NULL);
	if (!set_split_str(s, c, split_strs))
		return (free_2d_array(&split_strs));
	split_strs[len] = NULL;
	return (split_strs);
}

/*
#include <stdio.h>

static void	put_and_free(char **strs)
{
    size_t	i;

	i = 0;
    while (strs[i]) {
        printf("%s\n", strs[i]);
        free(strs[i]);
        i++;
    }
    free(strs);
}

int main(void) {
    put_and_free(ft_split("  abcd       efg hi  ", ' '));
    put_and_free(ft_split("  abcd       efg hi", ' '));
    put_and_free(ft_split("abcd       efg hi  ", ' '));
    put_and_free(ft_split("abcd       efg hi", ' '));
    put_and_free(ft_split("", ' '));
    put_and_free(ft_split("", '\0'));
    put_and_free(ft_split("abcd", '\0'));
    return 0;
}
*/
