#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ms_signal.h"
#include "ms_tokenize.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_sys.h"
#include "ft_mem.h"

static int	g_sig = INIT_SIG;

void	sigint_handler_for_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		rl_done = true;
	}
}

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
	return (0);
}

static void	set_signal_in_heredoc(bool is_interactive)
{
	set_signal_for_heredoc();
	if (is_interactive)
	{
		rl_catch_signals = true;
		rl_event_hook = event_by_sigint_for_heredoc;
	}
}

t_result	read_input_save_to_fd(int fd, \
									const char *delimiter, \
									bool is_interactive)
{
	char	*line;

	set_signal_in_heredoc(is_interactive);
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
			ft_free(&line);
			g_sig = INIT_SIG;
			return (BREAK);
		}
		if (ft_streq(line, delimiter))
		{
			ft_free(&line);
			return (SUCCESS);
		}
		ft_dprintf(fd, "%s\n", line);
		ft_free(&line);
	}
}
