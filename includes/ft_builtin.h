#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include <stdbool.h>

// todo: naming...
# define EXIT_ONLY_CMD_CNT		1
# define EXIT_ARG_IDX			1
# define VALID_ARG_CNT			2

# define NON_NUMERIC_ARG_STATUS	2
# define TOO_MANY_ARG_STATUS	1

# define BYTE_MASK				0xFF

typedef enum e_exit_argument
{
	EXIT_VALID_ARG,
	EXIT_NON_NUMERIC_ARG,
	RETURN_TOO_MANY_NUMERIC_ARG,
}	t_exit_arg;

int		ft_echo(char **cmds);
int		ft_exit(const char **cmds, bool *is_exit_shell);
bool	ft_legal_number(const char *str, long *result);
bool	is_builtin_func(char *cmd);
int		call_builtin_func(char **command, bool *is_exit_shell);

#endif //FT_BUILTIN_H
