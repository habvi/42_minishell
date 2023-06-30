#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

// pwd arg1 arg2 arg3 ... -> pwd, $?=0
// pwd op                 -> invalid op, $?=2
static char	*get_pwd(t_context *context)
{
	char	*pwd;

	(void)context;
	pwd = get_working_directory(CMD_PWD);
//	if (!pwd && context->internal_pwd) // for mac and rm $PWD
//	{
//		pwd = ft_strdup(context->internal_pwd);
//		if (!pwd)
//			ft_abort();
//		return (pwd);
//	}
	return (pwd);
}

uint8_t	ft_pwd(const char *const *argv, t_context *context)
{
	uint8_t	status;
	size_t	i;
	char	*pwd;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	pwd = get_pwd(context);
	if (!pwd)
		return (EXIT_FAILURE); // todo:tmp
	ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
	ft_free(&pwd);
	return (status);
}
