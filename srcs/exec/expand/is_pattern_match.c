#include "minishell.h"
#include "ft_mem.h"
#include "ft_string.h"

static void	swap_dp_table(bool **dp, bool **ndp, const size_t len_target)
{
	bool	*tmp;

	tmp = *dp;
	*dp = *ndp;
	*ndp = tmp;
	ft_memset(*ndp, false, sizeof(bool) * (len_target + 1));
}

bool	is_pattern_match_target_path(const char *match_str, const char *target_path)
{
	const size_t	len_match = ft_strlen(match_str);
	const size_t	len_target = ft_strlen(target_path);
	size_t			i;
	size_t			j;
	bool			*dp;
	bool			*ndp;
	bool			answer;

	dp = (bool *)ft_calloc(len_target + 1, sizeof(bool));
	if (!dp)
		ft_abort();
	ndp = (bool *)ft_calloc(len_target + 1, sizeof(bool));
	if (!ndp)
		ft_abort();
	dp[0] = true;

	i = 1;
	while (i < len_match + 1)
	{
		if (match_str[i - 1] == '*') // todo: macro
			ndp[0] = dp[0];
		j = 1;
		while (j < len_target + 1)
		{
			if (match_str[i - 1] == '*') // todo: macro
				ndp[j] = ndp[j - 1] || dp[j - 1] || dp[j];
			else if (target_path[j - 1] == match_str[i - 1])
				ndp[j] = dp[j - 1];
			j++;
		}
		swap_dp_table(&dp, &ndp, len_target);
		i++;
	}
	answer = dp[len_target];
	ft_free(&dp);
	ft_free(&ndp);
	return (answer);
}
