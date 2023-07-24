#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"
#include "ms_signal.h"
#include "ms_tokenize.h"
#include "ft_mem.h"
#include "ft_sys.h"

extern volatile sig_atomic_t	g_sig;

static void	sigint_handler_for_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		rl_done = true;
	}
}

void	set_signal_for_heredoc(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	init_sigaction(&sigint_act, sigint_handler_for_heredoc, FLAG_NONE);
	if (x_sigaction(SIGINT, &sigint_act, NULL) == SIGACT_ERROR)
		ft_abort();
	init_sigaction(&sigquit_act, SIG_IGN, FLAG_NONE);
	if (x_sigaction(SIGQUIT, &sigquit_act, NULL) == SIGACT_ERROR)
		ft_abort();
}
