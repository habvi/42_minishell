#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ms_var.h"
#include "ft_mem.h"
#include "ft_string.h"

static bool	is_slash_in_argv(const char *const argv_head)
{
	if (!argv_head)
		return (false);
	if (ft_strchr_bool(argv_head, PATH_DELIMITER_CHR))
		return (true);
	return (false);
}

static bool	is_empty_command(const char *const command)
{
	return (command && !*command);
}

// access(PATH[i] + "/" " command)
static char	*search_command_path(const char *const command, \
									t_var *var, \
									size_t paths_len, \
									t_result *result)
{
	char	*env_path;
	char	*exec_path;

	*result = SUCCESS;
	if (is_empty_command(command))
		return (NULL);
	if (ft_streq(command, PATH_DOT))
		return (NULL);
	if (paths_len > 0 && ft_streq(command, PATH_DOT_DOT))
		return (NULL);
	env_path = create_split_src_paths(var, KEY_PATH);
	exec_path = create_executable_path(env_path, command, result);
	if (exec_path)
	{
		ft_free((void **)&env_path);
		return (exec_path);
	}
	exec_path = create_accessible_path(env_path, command, result);
	ft_free((void **)&env_path);
	return (exec_path);
}

// if search_command_path return NULL -> command not found
static char	*create_exec_path_inter(const char *const *argv, \
							t_var *var, \
							size_t paths_len, \
							t_result *result)
{
	char	*path;

	if (is_slash_in_argv(argv[0]))
		path = x_ft_strdup(argv[0]);
	else
		path = search_command_path(argv[0], var, paths_len, result);
	return (path);
}

char	*create_exec_path(const char *const *argv, \
							t_var *var, \
							size_t paths_len, \
							t_context *context)
{
	const char *const	command = argv[0];
	char				*exec_path;
	t_result			result;
	bool				is_dir;

	exec_path = create_exec_path_inter(argv, var, paths_len, &result);
	if (result == PROCESS_ERROR)
		return (ft_free((void **)&exec_path));
	if (!exec_path)
	{
		put_path_err_set_status(command, context, paths_len);
		return (ft_free((void **)&exec_path));
	}
	is_dir = is_a_directory(exec_path, &result);
	if (result == PROCESS_ERROR)
		return (ft_free((void **)&exec_path));
	if (is_dir)
	{
		puterr_cmd_msg_set_status(\
			command, strerror(EISDIR), context, STATUS_IS_A_DIRECTORY);
		return (ft_free((void **)&exec_path));
	}
	return (exec_path);
}
