#include "ft_dprintf.h"
#include "ft_mem.h"
#include "ft_string.h"

// static void	debug_print_dp_target_str(const char *target_path, const size_t len_target)
// {
// 	ft_dprintf(2, "    ");
// 	for (size_t i = 0; i < len_target + 1; i++) {
// 		ft_dprintf(2, "%c ", target_path[i]);
// 	}
// 	ft_dprintf(2, "\n");
// }

// static void debug_print_each_dp(const bool *dp, const char *match_str, const size_t len_t, size_t i)
// {
// 	if (i == 1)
// 		ft_dprintf(2, "  ");
// 	if (i >= 2)
// 		ft_dprintf(2, "%c ", match_str[i - 2]);
// 	for (size_t j = 0; j < len_t + 1; j++) {
// 		ft_dprintf(2, "%d ", dp[j]);
// 	}
// 	ft_dprintf(2, "\n");
// }

bool	is_pattern_match_target_path(const char *match_str, const char *target_path)
{
	const size_t	len_match = ft_strlen(match_str);
	const size_t	len_target = ft_strlen(target_path);
	size_t			i;
	size_t			j;
	bool			*dp;
	bool			*ndp;
	bool			answer;

	// debug_print_dp_target_str(target_path, len_target);
	dp = (bool *)ft_calloc(len_target + 1, sizeof(bool)); // todo: sizeif(bool)...?
	dp[0] = true;

	i = 1;
	while (i < len_match + 1)
	{
		ndp = (bool *)ft_calloc(len_target + 1, sizeof(bool));
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
		// debug_print_each_dp(dp, match_str, len_target, i);
		ft_free(&dp);
		dp = ndp;
		i++;
	}
	// debug_print_each_dp(dp, match_str, len_target, i);
	answer = dp[len_target];
	ft_free(&dp);
	return (answer);
}
