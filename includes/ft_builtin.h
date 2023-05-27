#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

typedef enum e_exit_argument
{
	EXIT_VALID_ARG,
	EXIT_NON_NUMERIC_ARG,
	NOT_EXIT_TOO_MANY_NUMERIC_ARG,
}	t_exit_arg;

int	ft_echo(char **cmds);

#endif //FT_BUILTIN_H
