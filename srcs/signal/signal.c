#include <signal.h>
#include "minishell.h"
#include "ms_signal.h"
#include "ft_mem.h"
#include "ft_sys.h"

static void	init_sigaction(struct sigaction *act, \
							void (*handler)(int sig), \
							int flag)
{
	ft_bzero(act, sizeof(struct sigaction));
	sigemptyset(&act->sa_mask);
	act->sa_handler = handler;
	act->sa_flags = flag;
}

void	set_signal_for_prompt(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	init_sigaction(&sigint_act, sigint_handler_for_prompt, 0); // todo:flag
	if (x_sigaction(SIGINT, &sigint_act, NULL) == SIGACT_ERROR)
		ft_abort();

	init_sigaction(&sigquit_act, SIG_IGN, 0);
	if (x_sigaction(SIGQUIT, &sigquit_act, NULL) == SIGACT_ERROR)
		ft_abort();
}

void	set_signal_for_heredoc(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	init_sigaction(&sigint_act, sigint_handler_for_heredoc, 0); // todo:flag
	if (x_sigaction(SIGINT, &sigint_act, NULL) == SIGACT_ERROR)
		ft_abort();

	init_sigaction(&sigquit_act, SIG_IGN, 0);
	if (x_sigaction(SIGQUIT, &sigquit_act, NULL) == SIGACT_ERROR)
		ft_abort();
}

void	set_signal_for_parent(void)
{
	struct sigaction	sigquit_act;
	init_sigaction(&sigquit_act, SIG_IGN, 0);
	if (x_sigaction(SIGQUIT, &sigquit_act, NULL) == SIGACT_ERROR)
		ft_abort();
}

void	set_signal_for_child(void)
{
	struct sigaction	sigquit_act;
	init_sigaction(&sigquit_act, SIG_DFL, 0);
	if (x_sigaction(SIGQUIT, &sigquit_act, NULL) == SIGACT_ERROR)
		ft_abort();
}
