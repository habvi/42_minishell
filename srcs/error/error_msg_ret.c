#include "minishell.h"
#include "ms_builtin.h"

bool	puterr_msg_quoted_arg_ret_bool(const char *msg, \
										const char *const arg, \
										bool ret)
{
	puterr_msg_quoted_arg(msg, arg);
	return (ret);
}
