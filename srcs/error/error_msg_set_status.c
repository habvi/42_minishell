#include "minishell.h"
#include "ms_exec.h"

void	puterr_cmd_msg_set_status(const char *const cmd, \
									const char *msg, \
									t_context *context, \
									uint8_t status)
{
	puterr_cmd_msg(cmd, msg);
	context->status = status;
}

void	put_path_err_set_status(const char *const cmd, \
								t_context *context, \
								size_t paths_len)
{
	if (paths_len == 0)
	{
		puterr_cmd_msg_set_status(\
			cmd, ERROR_MSG_NO_SUCH_FILE, context, STATUS_NO_SUCH_FILE);
	}
	else
	{
		puterr_cmd_msg_set_status(\
			cmd, ERROR_MSG_CMD_NOT_FOUND, context, STATUS_CMD_NOT_FOUND);
	}
}
