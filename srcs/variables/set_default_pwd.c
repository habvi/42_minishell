#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"

t_result	set_default_pwd(t_var *var)
{
	char		*pwd_path;
	t_result	result;

	pwd_path = get_working_directory(SHELL_INIT, &result);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (pwd_path)
	{
		var->add(var, KEY_PWD, pwd_path, VAR_ENV);
		ft_free((void **)&pwd_path);
	}
	return (SUCCESS);
}
