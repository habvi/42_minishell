#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_string.h"
#include "ft_mem.h"

static bool	is_slash_in_argv(const char *const argv_head)
{
	if (!argv_head)
		return (false);
	if (ft_strchr_bool(argv_head, PATH_DELIMITER_CHR))
		return (true);
	return (false);
}

char	*create_split_src_paths(t_var *var, const char *key)
{
	char	*env_path;
	char	*env_path_concat_colon;

	env_path = var->get_value(var, key);
	env_path_concat_colon = x_ft_strjoin(env_path, STR_PATH_DELIMITER);
	ft_free(&env_path);
	return (env_path_concat_colon);
}

// access(PATH[i] + "/" " command)
static char	*search_command_path(const char *const command, t_var *var)
{
	char	*env_path;
	char	*exec_path;

	env_path = create_split_src_paths(var, KEY_PATH);
	exec_path = create_executable_path(env_path, command);
	if (exec_path)
	{
		ft_free(&env_path);
		return (exec_path);
	}
	exec_path = create_accessible_path(env_path, command);
	ft_free(&env_path);
	return (exec_path);
}

// todo move /path
// if search_command_path return NULL -> command not found
char	*create_exec_path(const char *const *argv, t_var *var)
{
	char	*path;

	if (is_slash_in_argv(argv[0]))
		path = x_ft_strdup(argv[0]);
	else
		path = search_command_path(argv[0], var);
	return (path);
}
