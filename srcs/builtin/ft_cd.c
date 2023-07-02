#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_dprintf.h"
#include "ft_mem.h"

void	update_pwd_in_cd(t_var *var, \
							const char *key, \
							const char *value, \
							t_var_attr attr)
{
	t_var_info	*var_info;
	char		*dup_value;

	dup_value = x_ft_strdup(value);
	var_info = var_create_var_info_for_set(var, key, dup_value, attr);
	var->add(var, key, var_info);
	del_var_info((void **)&var_info);
}

static bool	is_valid_cd_path(const char *path, int *tmp_err)
{
	if (!path)
		return (false);
	if (!test_opendir(path, tmp_err))
		return (false);
	return (true);
}

static void	change_directory(const char *arg, \
								t_context *context, \
								uint8_t *status)
{
	char		*path;
	int			tmp_err;
	t_result	result;

	path = cd_set_path(arg, context->var);
	if (!is_valid_cd_path(path, &tmp_err))
	{
		ft_dprintf(2, "cd: invalid path\n"); // todo: tmp
//		print_err_set_status(arg, path, tmp_err, status);
		ft_free(&path);
		return ;
	}
	result = cd_change_dir_to_valid_path(path, context->internal_pwd, status);
	if (result == FAILURE)
	{
		ft_dprintf(2, "cd: fail to chdir\n"); // todo: tmp
		ft_free(&path);
		return ;
	}
	cd_update_pwd(path, context);
}

uint8_t	ft_cd(const char *const *argv, t_context *context)
{
	uint8_t	status;
	size_t	i;
	size_t	args;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	args = count_argv(&argv[i]);
	if (args > 1)
	{
		status = TOO_MANY_ARG_STATUS;
		// print_error(); // todo
		return (status);
	}
	change_directory(argv[i], context, &status);
	return (EXIT_SUCCESS);
}
