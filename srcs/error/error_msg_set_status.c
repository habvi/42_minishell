#include "minishell.h"
#include "ms_builtin.h"

void	puterr_cmd_msg_set_status(const char *const cmd, \
									const char *msg, \
									t_context *context, \
									uint8_t status)
{
	puterr_cmd_msg(cmd, msg);
	context->status = status;
}
