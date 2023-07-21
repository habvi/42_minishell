#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

# define INIT_SIG	0

void	set_signal_for_prompt(void);
void	set_signal_for_heredoc(void);
void	sigint_handler_for_prompt(int sig);
void	sigint_handler_for_heredoc(int sig);

#endif //MS_SIGNAL_H
