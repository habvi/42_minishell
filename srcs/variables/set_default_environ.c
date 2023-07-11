#include "minishell.h"
#include "ms_var.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_sys.h"

void	del_var_info(void **var_info)
{
	t_var_info	*tmp_info;

	if (!var_info || !*var_info)
		return ;
	tmp_info = (t_var_info *)*var_info;
	ft_free(&tmp_info->value);
	ft_free(&tmp_info);
	*var_info = NULL;
}

static void	set_func(t_var *var)
{
	var->is_key_exist = var_is_key_exist;
	var->get_value = var_get_value;
	var->add = var_add;
	var->unset = var_unset;
	var->print_detail = var_print_detail;
	var->clear = var_clear;
	var->join = var_join;
	var->env_print = env_print;
	var->convert_to_envp = var_convert_to_envp;
}

static void	get_environ(t_var *var)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	if (!environ)
		return ;
	while (environ[i])
	{
		var_declare_arg(environ[i], var, VAR_ENV);
		i++;
	}
}

static void	set_env_default_hash(t_var *var)
{
	var->hash = hs_create_table(VAR_LIST_SIZE, del_var_info);
	if (!var->hash)
		ft_abort();
	get_environ(var);
}

t_var	*set_default_environ(void)
{
	t_var	*var;

	var = (t_var *)x_malloc(sizeof(t_var));
	if (!var)
		ft_abort();
	set_func(var);
	set_env_default_hash(var);
	set_default_pwd(var);
	set_default_old_pwd(var);
	return (var);
}
