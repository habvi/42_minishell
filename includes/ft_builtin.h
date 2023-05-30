#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include <stdbool.h>

<<<<<<< HEAD
// todo: naming...
# define EXIT_ONLY_CMD_CNT		1
# define EXIT_ARG_IDX			1
# define VALID_ARG_CNT			2

# define NON_NUMERIC_ARG_STATUS	2
# define TOO_MANY_ARG_STATUS	1

# define BYTE_MASK				(0xFF)
=======
# define STR_ECHO	"echo"
# define STR_CD		"cd"
# define STR_PWD	"pwd"
# define STR_EXPORT	"export"
# define STR_UNSET	"unset"
# define STR_ENV	"env"
# define STR_EXIT	"exit"
>>>>>>> 9fa0d9e (update(calc_builtin): command str in header)

typedef enum e_exit_argument
{
	EXIT_VALID_ARG,
	EXIT_NON_NUMERIC_ARG,
	RETURN_TOO_MANY_NUMERIC_ARG,
}	t_exit_arg;

int		ft_echo(char **cmds);
<<<<<<< HEAD
int		ft_exit(const char **cmds, bool *is_exit_shell);
=======
int		ft_exit(char **cmds, bool *is_exit_shell);

>>>>>>> 07b4f47 (add(is_sigle_builtin))
bool	ft_legal_number(const char *str, long *result);
bool	is_builtin_func(char *cmd);
bool	is_single_builtin(t_deque_node *node, char *cmd);

int		call_builtin_func(char **command, bool *is_exit_shell);

#endif //FT_BUILTIN_H
