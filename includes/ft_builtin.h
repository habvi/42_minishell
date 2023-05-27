#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include <stdbool.h>

typedef enum e_exit_argument
{
	EXIT_VALID_ARG,
	EXIT_NON_NUMERIC_ARG,
	NOT_EXIT_TOO_MANY_NUMERIC_ARG,
}	t_exit_arg;

<<<<<<< HEAD
int	ft_echo(char **cmds);
=======
int		ft_echo(char **cmds);
int		ft_exit(char **cmds);
bool	ft_legal_number(const char *str, long *result);
>>>>>>> 3f634aa (add(ft_legal_number):implement ft_legal_number and add simple test)

#endif //FT_BUILTIN_H
