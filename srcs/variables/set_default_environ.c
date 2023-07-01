#include "minishell.h"
#include "ms_var.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_sys.h"

void	del_var_info(void **var_info)
{
	t_var_info	*info;

	if (!var_info || !*var_info)
		return ;
	info = (t_var_info *)*var_info;
	ft_free(&info->value);
	ft_free(&info);
	*var_info = NULL;
}

static void	set_func(t_var *var)
{
	var->is_key_exist = env_is_key_exist;
	var->get_value = env_get_value;
	var->add = env_add;
	var->join = env_join;
	var->unset = env_unset;
	var->print = env_print;
	var->print_detail = env_print_detail;
	var->clear = env_clear;
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
		env_declare_arg(environ[i], var, VAR_ENV);
		i++;
	}
}

static void	set_env_default_hash(t_var *var)
{
	var->hash = hs_create_table(ENV_LIST_SIZE, del_var_info);
	if (!var->hash)
		ft_abort();
	get_environ(var);
}

t_var	*set_default_environ(t_context *context)
{
	t_var	*var;

	var = (t_var *)x_malloc(sizeof(t_var));
	if (!var)
		ft_abort();
	context->var = var;
	set_func(var);
	set_env_default_hash(context->var);
	set_default_pwd(var);
	set_default_old_pwd(var); // todo
	return (var);
}
