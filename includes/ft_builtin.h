#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include <stdbool.h>
# include "deque.h"

# define STR_ECHO	"echo"
# define STR_CD		"cd"
# define STR_PWD	"pwd"
# define STR_EXPORT	"export"
# define STR_UNSET	"unset"
# define STR_ENV	"env"
# define STR_EXIT	"exit"

typedef enum e_exit_argument
{
	EXIT_VALID_ARG,
	EXIT_NON_NUMERIC_ARG,
	RETURN_TOO_MANY_NUMERIC_ARG,
}	t_exit_arg;

int		ft_echo(const char **cmds);
int		ft_exit(const char **cmds, bool *is_exit_shell);

bool	ft_legal_number(const char *str, long *result);
bool	is_builtin_func(const char *cmd);
bool	is_single_builtin(t_deque_node *node, const char *cmd);

int		call_builtin_func(const char **command, bool *is_exit_shell);

#endif //FT_BUILTIN_H
