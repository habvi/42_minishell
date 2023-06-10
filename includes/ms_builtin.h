#ifndef MS_BUILTIN_H
# define MS_BUILTIN_H

# include <stdbool.h>

# define CMD_ECHO	"echo"
# define CMD_CD		"cd"
# define CMD_PWD	"pwd"
# define CMD_EXPORT	"export"
# define CMD_UNSET	"unset"
# define CMD_ENV	"env"
# define CMD_EXIT	"exit"

# define CMD_OPTION_MARKER	'-'
# define ECHO_OPTION		'n'
# define ECHO_SEPARATOR		' '

// todo: naming...
# define EXIT_ONLY_CMD_CNT		1
# define EXIT_ARG_IDX			1
# define VALID_ARG_CNT			2

# define NON_NUMERIC_ARG_STATUS	2
# define TOO_MANY_ARG_STATUS	1

# define BYTE_MASK				(0xFF)

# define ERROR_MSG_TOO_MANY_ARG	"too many arguments"
# define ERROR_MSG_REQUIRED_NUM	"numeric argument required"

typedef struct s_deque_node	t_deque_node;
typedef struct s_params		t_params;

typedef enum e_exit_argument
{
	EXIT_VALID_ARG,
	EXIT_NON_NUMERIC_ARG,
	RETURN_TOO_MANY_NUMERIC_ARG,
}	t_exit_arg;

int		ft_echo(char *const *command);
int		ft_exit(char *const *command, t_params *params);

bool	is_legal_number(const char *str, long *result);
bool	is_command_builtin(const char *cmd);
bool	is_single_builtin(t_deque_node *cmd);

#endif //MS_BUILTIN_H
