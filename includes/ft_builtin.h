#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include <stdbool.h>

typedef enum e_exit_argument_stat
{
	EXIT_VALID_ARG,
	EXIT_NON_NUMERIC_ARG,
	RETURN_TOO_MANY_NUMERIC_ARG,
}	t_exit_arg;

int		ft_echo(char **cmds);
int		ft_exit(char **cmds);
bool	ft_legal_number(const char *str, long *result);

#endif //FT_BUILTIN_H
