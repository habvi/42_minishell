#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

# define INIT_SIG	0
# define FLAG_NONE	0

void	set_signal_for_prompt(void);
void	set_signal_for_heredoc(void);
void	set_signal_for_parent(void);
void	set_signal_for_child(void);

void	init_sigaction(struct sigaction *act, \
						void (*handler)(int sig), \
						int flag);

#endif //MS_SIGNAL_H
