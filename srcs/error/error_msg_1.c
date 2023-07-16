#include "minishell.h"

void	puterr_cmd_msg(const char *const cmd, const char *msg)
{
	ft_dprintf(STDERR_FILENO, \
			"%s: %s: %s\n", \
			SHELL_NAME, cmd, msg);

}

void	puterr_cmd_arg_msg(const char *cmd, \
							const char *const arg, \
							const char *msg)
{
	ft_dprintf(STDERR_FILENO, \
			"%s: %s: %s: %s\n", \
			SHELL_NAME, cmd, arg, msg);

}

void	puterr_cmd_arg_msg_wo_colon(const char *cmd, \
									const char *const arg, \
									const char *msg)
{
	ft_dprintf(STDERR_FILENO, \
			"%s: %s: %s %s\n", \
			SHELL_NAME, cmd, arg, msg);

}

void	puterr_msg_quoted_arg(const char *msg, const char *const arg)
{
	ft_dprintf(STDERR_FILENO, \
				"%s: %s `%s'\n", \
				SHELL_NAME, msg, arg);
}

void	puterr_cmd_quoted_arg_msg(const char *cmd, \
								const char *const arg, \
								const char *msg)
{
	ft_dprintf(STDERR_FILENO, \
			"%s: %s: `%s': %s\n", \
			SHELL_NAME, cmd, arg, msg);

}
