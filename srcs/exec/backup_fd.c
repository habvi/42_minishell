#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_result.h"
#include "ft_string.h"
#include "ft_sys.h"

static bool	is_command_not_used_redirect(const char *command)
{
	return (ft_streq(command, CMD_EXIT));
}

// can't use is_use_redirect_in/out..., causes input file is output file...??
t_result	backup_stdio_fd(int *stdin_copy, \
							int *stdout_copy, \
							const t_ast *self_node)
{
	const char	*command = get_head_token_str(self_node->command);

	*stdin_copy = IN_FD_INIT;
	*stdout_copy = OUT_FD_INIT;
	if (is_command_not_used_redirect(command))
		return (SUCCESS);
	*stdin_copy = x_dup(STDIN_FILENO);
	if (*stdin_copy == DUP_ERROR)
		return (PROCESS_ERROR);
	*stdout_copy = x_dup(STDOUT_FILENO);
	if (*stdout_copy == DUP_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

t_result	restore_stdio_fd(int stdin_copy, int stdout_copy)
{
	if (stdin_copy != IN_FD_INIT)
	{
		if (x_close(STDIN_FILENO) == CLOSE_ERROR)
			return (PROCESS_ERROR);
		if (x_dup2(stdin_copy, STDIN_FILENO) == DUP_ERROR)
			return (PROCESS_ERROR);
		if (x_close(stdin_copy) == CLOSE_ERROR)
			return (PROCESS_ERROR);
	}
	if (stdout_copy != OUT_FD_INIT)
	{
		if (x_close(STDOUT_FILENO) == CLOSE_ERROR)
			return (PROCESS_ERROR);
		if (x_dup2(stdout_copy, STDOUT_FILENO) == DUP_ERROR)
			return (PROCESS_ERROR);
		if (x_close(stdout_copy) == CLOSE_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
