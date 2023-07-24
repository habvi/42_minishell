#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ms_signal.h"
#include "ms_tokenize.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

extern volatile sig_atomic_t	g_sig;

static char	*input_line_for_heredoc(void)
{
	char	*line;

	rl_outstream = stderr;
	line = readline(HEREDOC_PROMPT);
	if (!line)
		return (NULL);
	return (line);
}

static int	event_by_sigint_for_heredoc(void)
{
	if (g_sig == SIGINT)
		rl_done = false;
	return (EXIT_SUCCESS);
}

static void	set_signal_in_heredoc(t_context *context)
{
	set_signal_for_heredoc();
	if (!context->is_rl_event_hook_off)
	{
		rl_catch_signals = true;
		rl_event_hook = event_by_sigint_for_heredoc;
	}
}

static void	set_status_and_init_sig_var(t_context *context)
{
	context->status = SIGINT + STATUS_SIG_BASE;
	g_sig = INIT_SIG;
}

t_result	read_input_save_to_fd(int fd, \
									const char *delimiter, \
									t_context *context)
{
	char	*line;

	set_signal_in_heredoc(context);
	while (true)
	{
		line = input_line_for_heredoc();
		if (!line)
		{
			puterr_heredoc_wanted_eof(delimiter);
			return (SUCCESS);
		}
		if (g_sig == SIGINT)
		{
			ft_free((void **)&line);
			set_status_and_init_sig_var(context);
			return (BREAK);
		}
		if (ft_streq(line, delimiter))
		{
			ft_free((void **)&line);
			return (SUCCESS);
		}
		ft_dprintf(fd, "%s\n", line);
		ft_free((void **)&line);
	}
}
