#include "minishell.h"
#include "ft_dprintf.h"

/*
usage

bool	is_pattern_match_target_path(const char *match_str, const char *target_path
{
	debug_print_dp_target_str(target_path, len_target);
	while
	{
		debug_print_each_dp(dp, match_str, len_target, i);
		swap_dp_table(&dp, &ndp, len_target);
	}
	debug_print_each_dp(dp, match_str, len_target, i);
	ft_dprintf(2, "--------------------------\n");
}
*/
void	debug_print_dp_target_str(const char *target_path, \
									const size_t len_target)
{
	size_t	i;

	ft_dprintf(2, "    ");
	i = 0;
	while (i < len_target + 1)
	{
		ft_dprintf(2, "%c ", target_path[i]);
		i++;
	}
	ft_dprintf(2, "\n");
}

void	debug_print_each_dp(const bool *dp, \
							const char *match_str, \
							const size_t len_t, \
							size_t i)
{
	size_t	j;

	if (i == 1)
		ft_dprintf(2, "  ");
	if (i >= 2)
		ft_dprintf(2, "%c ", match_str[i - 2]);
	j = 0;
	while (j < len_t + 1)
	{
		ft_dprintf(2, "%d ", dp[j]);
		j++;
	}
	ft_dprintf(2, "\n");
}
