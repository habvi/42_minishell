#include "minishell.h"
#include "ms_signal.h"
#include "ft_sys.h"
#include "ft_mem.h"

extern volatile sig_atomic_t	g_sig;

static void	sigint_handler_for_prompt(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
	}
}

void	set_signal_for_prompt(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	init_sigaction(&sigint_act, sigint_handler_for_prompt, FLAG_NONE);
	if (x_sigaction(SIGINT, &sigint_act, NULL) == SIGACT_ERROR)
		ft_abort();
	init_sigaction(&sigquit_act, SIG_IGN, FLAG_NONE);
	if (x_sigaction(SIGQUIT, &sigquit_act, NULL) == SIGACT_ERROR)
		ft_abort();
}
