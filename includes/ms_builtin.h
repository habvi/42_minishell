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

// todo: naming...
# define EXIT_ONLY_CMD_CNT		1
# define EXIT_ARG_IDX			1
# define VALID_ARG_CNT			2

# define NON_NUMERIC_ARG_STATUS	2
# define TOO_MANY_ARG_STATUS	1

# define BYTE_MASK				(0xFF)

typedef struct s_deque_node	t_deque_node;

typedef enum e_exit_argument
{
	EXIT_VALID_ARG,
	EXIT_NON_NUMERIC_ARG,
	RETURN_TOO_MANY_NUMERIC_ARG,
}	t_exit_arg;

int		ft_echo(const char **cmds);
int		ft_exit(const char **cmds, bool is_interactive);

bool	ft_legal_number(const char *str, long *result);
bool	is_command_builtin(const char *cmd);
bool	is_single_builtin(t_deque_node *node);

int		call_builtin_command(const char **command, bool is_interactive);

#endif //MS_BUILTIN_H
