#include "minishell.h"
#include "ms_builtin.h"

void	puterr_arg_op_msg(const char *const arg, const char op)
{
	ft_dprintf(STDERR_FILENO, \
				"%s: %s: %c%c: %s\n", \
				SHELL_NAME, arg, CMD_OPTION_MARKER, op, ERROR_MSG_INVALID_OP);
}

void	puterr_heredoc_wanted_eof(const char *delimiter)
{
	ft_dprintf(STDERR_FILENO, \
			"%s: %s: %s (wanted `%s')\n", \
			SHELL_NAME, ERROR_TYPE_WARNING, ERROR_MSG_HEREDOC_EOF, delimiter);
}

void	puterr_whom_cmd_arg_msg(const char *for_whom,
								const char *cmd, \
								const char *const arg, \
								const char *msg)
{
	ft_dprintf(STDERR_FILENO, \
			"%s: %s: %s: %s\n", \
			for_whom, cmd, arg, msg);
}

void	puterr_env_option(const char *const arg)
{
	ft_dprintf(STDERR_FILENO, \
				"%s: %s '%s'\n", \
				CMD_ENV, ERROR_MSG_INVALID_OP, arg);
}

void	puterr_env_argument(const char *const arg)
{
	ft_dprintf(STDERR_FILENO, \
				"%s: ‘%s’: %s\n", \
				CMD_ENV, arg, ERROR_MSG_INVALID_ARG);
}
