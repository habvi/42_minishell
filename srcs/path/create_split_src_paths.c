#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"

char	*create_split_src_paths(t_var *var, const char *key)
{
	char	*env_path;
	char	*env_path_concat_colon;

	env_path = var->get_value(var, key);
	env_path_concat_colon = x_ft_strjoin(env_path, STR_PATH_DELIMITER);
	ft_free((void **)&env_path);
	return (env_path_concat_colon);
}
