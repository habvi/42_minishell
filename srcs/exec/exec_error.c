#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ms_var.h"
#include "ft_mem.h"
#include "ft_string.h"

uint8_t	err_is_a_dir_and_ret_status(const char *const cmd, \
									t_context *context, \
									char **exec_path)
{
	puterr_cmd_msg_set_status(\
		cmd, strerror(EISDIR), context, STATUS_IS_A_DIRECTORY);
	ft_free(exec_path);
	return (context->status);
}

static uint8_t	err_cmd_not_found_and_ret_status(const char *const cmd, \
													t_context *context, \
													char **exec_path)
{
	puterr_cmd_msg_set_status(\
		cmd, ERROR_MSG_CMD_NOT_FOUND, context, STATUS_CMD_NOT_FOUND);
	ft_free(exec_path);
	return (context->status);
}

static uint8_t	err_no_such_file_and_ret_status(const char *const cmd, \
												t_context *context, \
												char **exec_path)
{
	puterr_cmd_msg_set_status(\
		cmd, ERROR_MSG_NO_SUCH_FILE, context, STATUS_NO_SUCH_FILE);
	ft_free(exec_path);
	return (context->status);
}

uint8_t	err_and_ret_status(const char *const cmd, \
							t_context *context, \
							char **exec_path, \
							size_t paths_len)
{
	if (paths_len == 0)
		return (err_no_such_file_and_ret_status(cmd, context, exec_path));
	return (err_cmd_not_found_and_ret_status(cmd, context, exec_path));
}
