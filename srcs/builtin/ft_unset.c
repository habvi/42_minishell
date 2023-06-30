#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ft_mem.h"
#include "ft_string.h"

static void	unset_internal_pwd(t_context *context)
{
	ft_free(&context->internal_pwd);
}

static void	unset_internal_old_pwd(t_context *context)
{
	ft_free(&context->internal_old_pwd);
}

static void	unset_args(const char *const *args, \
						t_context *context, \
						uint8_t *status)
{
	t_env	*env;
	size_t	i;

	env = context->env;
	i = 0;
	while (args[i])
	{
		if (is_valid_key(args[i]))
		{
			env->unset(env, args[i]);
			if (ft_streq(args[i], KEY_PWD))
				unset_internal_pwd(context);
			else if (ft_streq(args[i], KEY_OLDPWD))
				unset_internal_old_pwd(context);
		}
		else
			*status = NOT_A_VALID_IDENTIFIER; // print error
		i++;
	}
}

uint8_t	ft_unset(const char *const *argv, t_context *context)
{
	uint8_t	status;
	size_t	i;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	unset_args(&argv[i], context, &status);
	return (status);
}
