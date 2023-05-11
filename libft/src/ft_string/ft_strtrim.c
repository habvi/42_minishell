#include "ft_string.h"

static char const	*search_set(\
		char const *s, char const *set, const size_t len_s, const int direction)
{
	size_t	i;

	i = 0;
	while (i < len_s && ft_strchr(set, *s))
	{
		s += direction;
		i++;
	}
	return (s);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len_s;
	char const	*head = s1;
	char const	*tail = s1;
	size_t		total;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	len_s = ft_strlen(s1);
	total = 0;
	if (len_s)
	{
		head = search_set(s1, set, len_s, 1);
		tail = search_set(s1 + len_s - 1, set, len_s, -1);
		if (head <= tail)
			total = tail - head + 1;
	}
	return (ft_substr(s1, head - s1, total));
}

// #include <stdio.h>

// static void	put_and_free(char *s)
// {
// 	printf("%s\n", s);
// 	free(s);
// }

// int main(void)
// {
// 	put_and_free(ft_strtrim("///abcd////", "/"));
// 	put_and_free(ft_strtrim("////////", "/"));
// 	put_and_free(ft_strtrim("abcd", "/"));
// 	put_and_free(ft_strtrim("//abcd", "/"));
// 	put_and_free(ft_strtrim("abcd////", "/"));
// 	put_and_free(ft_strtrim("", "/"));
// 	put_and_free(ft_strtrim("abcd", ""));
// 	put_and_free(ft_strtrim("", ""));
// }

/*
cc -fsanitize=address -I../include ft_strtrim.c ft_strchr.c \
ft_strdup.c ft_strlen.c ft_substr.c ft_strlcpy.c ft_strnlen.c \
ft_strndup.c ft_strlcpy_void.c && ./a.out
*/
