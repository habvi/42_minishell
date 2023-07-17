#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static void print_debug(const bool *dp, const char *match_str, const size_t len_t, size_t i)
{
	if (i == 1)
		printf("  ");
	if (i >= 2)
		printf("%c ", match_str[i - 2]);
	for (size_t j = 0; j < len_t + 1; j++) {
		printf("%d ", dp[j]);
	}
	printf("\n");
}

/*
            (target)
			    a b c d e f 
(wildcard)	  1 0 0 0 0 0 0 
			a 0 1 0 0 0 0 0 
			* 0 1 1 1 1 1 1 
			b 0 0 1 0 0 0 0 
			c 0 0 0 1 0 0 0 
			* 0 0 0 1 1 1 1 
			d 0 0 0 0 1 0 0 
			e 0 0 0 0 0 1 0 
			f 0 0 0 0 0 0 1 
*/
static bool	is_matches_wildcard_and_str(const char *match_str, const char *target_path)
{
	const size_t	len_m = strlen(match_str);
	const size_t	len_t = strlen(target_path);
	size_t			i;
	size_t			j;
	bool			*dp;
	bool			*ndp;
	bool			answer;

	printf("    ");
	for (size_t i = 0; i < len_t + 1; i++) {
		printf("%c ", target_path[i]);
	}
	printf("\n");

	dp = (bool *)calloc(len_t + 1, sizeof(bool));
	dp[0] = true;

	i = 1;
	while (i < len_m + 1)
	{
		ndp = (bool *)calloc(len_t + 1, sizeof(bool));
		if (match_str[i - 1] == '*')
			ndp[0] = dp[0];
		j = 1;
		while (j < len_t + 1)
		{
			if (match_str[i - 1] == '*')
				ndp[j] = ndp[j - 1] || dp[j - 1] || dp[j];
			else if (target_path[j - 1] == match_str[i - 1])
				ndp[j] = dp[j - 1];
			j++;
		}
		print_debug(dp, match_str, len_t, i);
		free(dp);
		dp = ndp;
		i++;
	}
	print_debug(dp, match_str, len_t, i);
	answer = dp[len_t];
	free(dp);
	return (answer);
}

static int    test_wildcard(int no, char *input_wild, char *test_str, bool expected)
{
    bool    ret = is_matches_wildcard_and_str(input_wild, test_str);
    printf("\n[TEST %02d] wildcard:%-10s, test_str:%-10s, ret:%d, expected:%d, res:%s\n", no, input_wild, test_str, ret, expected, ret == expected ? "\x1b[32mAC\x1b[0m" : "\x1b[31mWA\x1b[0m");
    printf("\n\n");
    if (ret == expected)
        return (0);
    return (1);
}

int main(void)
{
	char	*s = "abcdef";
	char	*p = "a*bc*def";

	printf("result: %d\n", is_matches_wildcard_and_str(p, s));

	int ng = 0;
	int no = 0;

	ng += test_wildcard(no++, "12345*", "12345", true);
    ng += test_wildcard(no++, "*", "a", true);
    ng += test_wildcard(no++, "**", "a", true);
    ng += test_wildcard(no++, "***", "a", true);
    ng += test_wildcard(no++, "*a", "a", true);
    ng += test_wildcard(no++, "a*", "a", true);
    ng += test_wildcard(no++, "*a*", "a", true);
    ng += test_wildcard(no++, "****a****", "a", true);
	ng += test_wildcard(no++, "i*", "infile", true);
    ng += test_wildcard(no++, "n*", "infile", false);
    ng += test_wildcard(no++, "*n*", "infile", true);
    ng += test_wildcard(no++, "**l", "infile", false);
    ng += test_wildcard(no++, "*e*", "infile", true);
    ng += test_wildcard(no++, "i*i*e", "infile", true);
    ng += test_wildcard(no++, "*i*n*f*i*l*e*", "infile", true);
    ng += test_wildcard(no++, "*1*", "file10", true);
    ng += test_wildcard(no++, "*a*", "hello", false);
    ng += test_wildcard(no++, "*abcx", "abc___abce___abcex", false);
    ng += test_wildcard(no++, "*abd*", "abc___abce_abd__abcex", true);
    ng += test_wildcard(no++, "*****aba*****ab", "baaababbbbbbbab", true);
    ng += test_wildcard(no++, "A*A*A*A**ABC*****ABX*AB*AB*B*B*B*ABC", "AxAxAxAxABCxAxAAABCxABCxABX1xxABX2xABX3xACxxxxxABXxABxABxxxxBxBxBxABC", true);
    ng += test_wildcard(no++, "A*A*A*A**ABC*****ABX*AB*AB*B*B*B*ABC", "AxAAABCxABCxABX1xxABX2xxxABX3xACxxxABXxABxxABxxxBxBxBxABC", true);
    ng += test_wildcard(no++, "A*A*A*A**ABC*****ABX*AB*AB*B*B*B*ABC", "AxAxAxAxABCxAxAAABCxABCxABX1xxABX2xABX3xACxxxxxABXxABxABxxxxBxBxABCD", false);
    ng += test_wildcard(no++, "A*A*A*A**ABC*****ABX*AB*AB*B*B*B*ABC", "AxAAABCxAbCxABX1xxABX2xxxABX3xACxxxABXxABxxABxxxBxBxBxABC", false);

	return (ng);
}
