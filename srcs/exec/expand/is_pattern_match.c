#include "minishell.h"
#include "ms_expansion.h"
#include "ft_mem.h"
#include "ft_string.h"

static void	allocate_dp_table(bool **dp, bool **ndp, const size_t len_target)
{
	*dp = (bool *)ft_calloc(len_target + 1, sizeof(bool));
	if (!*dp)
		ft_abort();
	*ndp = (bool *)ft_calloc(len_target + 1, sizeof(bool));
	if (!*ndp)
		ft_abort();
}

static bool	is_valid_wildcard(const char *s, \
								const size_t i, \
								const bool *is_quoted_arr)
{
	return (s[i] == WILDCARD && !is_quoted_arr[i]);
}

static void	swap_dp_table(bool **dp, bool **ndp, const size_t len_target)
{
	bool	*tmp;

	tmp = *dp;
	*dp = *ndp;
	*ndp = tmp;
	ft_memset(*ndp, false, sizeof(bool) * (len_target + 1));
}

static bool	is_pattern_match_and_clear_dp(bool **dp, \
											bool **ndp, \
											const size_t len_target)
{
	const bool	answer = (*dp)[len_target];

	ft_free((void **)dp);
	ft_free((void **)ndp);
	return (answer);
}

bool	is_pattern_match_target_path(const char *match_str, \
										const size_t len_match, \
										const char *target_path, \
										const bool *is_quoted_arr)
{
	const size_t	len_target = ft_strlen(target_path);
	size_t			i;
	size_t			j;
	bool			*dp;
	bool			*ndp;

	allocate_dp_table(&dp, &ndp, len_target);
	dp[0] = true;
	i = 0;
	while (++i < len_match + 1)
	{
		if (is_valid_wildcard(match_str, i - 1, is_quoted_arr))
			ndp[0] = dp[0];
		j = 0;
		while (++j < len_target + 1)
		{
			if (is_valid_wildcard(match_str, i - 1, is_quoted_arr))
				ndp[j] = (ndp[j - 1] || dp[j - 1] || dp[j]);
			else if (target_path[j - 1] == match_str[i - 1])
				ndp[j] = dp[j - 1];
		}
		swap_dp_table(&dp, &ndp, len_target);
	}
	return (is_pattern_match_and_clear_dp(&dp, &ndp, len_target));
}
