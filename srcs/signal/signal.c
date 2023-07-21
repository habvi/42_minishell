#include <signal.h>
#include "minishell.h"
#include "ms_signal.h"
#include "ft_mem.h"
#include "ft_sys.h"

void	init_sigaction(struct sigaction *act, \
						void (*handler)(int sig), \
						int flag)
{
	ft_bzero(act, sizeof(struct sigaction));
	if (sigemptyset(&act->sa_mask) == SIGEMPTY_ERROR)
		ft_abort();
	act->sa_handler = handler;
	act->sa_flags = flag;
}

void	set_signal_for_parent(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	init_sigaction(&sigint_act, SIG_IGN, FLAG_NONE);
	if (x_sigaction(SIGINT, &sigint_act, NULL) == SIGACT_ERROR)
		ft_abort();
	init_sigaction(&sigquit_act, SIG_IGN, FLAG_NONE);
	if (x_sigaction(SIGQUIT, &sigquit_act, NULL) == SIGACT_ERROR)
		ft_abort();
}

void	set_signal_for_child(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	init_sigaction(&sigint_act, SIG_DFL, FLAG_NONE);
	if (x_sigaction(SIGINT, &sigint_act, NULL) == SIGACT_ERROR)
		ft_abort();
	init_sigaction(&sigquit_act, SIG_DFL, FLAG_NONE);
	if (x_sigaction(SIGQUIT, &sigquit_act, NULL) == SIGACT_ERROR)
		ft_abort();
}
