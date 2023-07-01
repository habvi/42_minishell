#ifndef MS_BUILTIN_H
# define MS_BUILTIN_H

# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>

// todo: sort & indent
# define CMD_ECHO	"echo"
# define CMD_CD		"cd"
# define CMD_PWD	"pwd"
# define CMD_DECLARE	"declare"
# define CMD_EXPORT	"export"
# define CMD_UNSET	"unset"
# define CMD_ENV	"env"
# define CMD_EXIT	"exit"

# define CMD_OPTION_MARKER	'-'
# define ECHO_OPTION		'n'
# define ECHO_SEPARATOR		' '
# define END_OF_CMD_OPTION	"--"

// todo: naming...
# define EXIT_ONLY_CMD_CNT		1
# define EXIT_ARG_IDX			1
# define VALID_ARG_CNT			2

# define NON_NUMERIC_ARG_STATUS	2
# define TOO_MANY_ARG_STATUS	1

# define NOT_A_VALID_IDENTIFIER	1
# define INVALID_OPTION			2

# define BYTE_MASK				(0xFF)

# define ERROR_MSG_TOO_MANY_ARG	"too many arguments"
# define ERROR_MSG_REQUIRED_NUM	"numeric argument required"
# define ERROR_MSG_INVALID_OP	"invalid option"
# define ERROR_MSG_NOT_VALID_ID	"not a valid identifier"

typedef enum e_result		t_result;
typedef struct s_var		t_var;
typedef struct s_deque_node	t_deque_node;
typedef struct s_context	t_context;

// for exit
typedef enum e_exit_argument
{
	EXIT_VALID_ARG,
	EXIT_NON_NUMERIC_ARG,
	RETURN_TOO_MANY_NUMERIC_ARG,
}	t_exit_arg;

// for export
typedef enum e_env_op
{
	ENV_ADD,
	ENV_JOIN,
}	t_env_op;

uint8_t	ft_echo(const char *const *argv);
uint8_t	ft_env(const char *const *argv, t_var *var);
uint8_t	ft_exit(const char *const *argv, t_context *context);
uint8_t	ft_export(const char *const *argv, t_var *var);
uint8_t	ft_pwd(const char *const *argv, t_context *context);
uint8_t	ft_declare(const char *const *argv, t_var *var);
uint8_t	ft_unset(const char *const *argv, t_var *var);

bool	is_option(const char *word);
bool	is_end_of_option(const char *word);
bool	is_valid_option(const char *const *argv, uint8_t *status, size_t *i);
bool	str_to_legal_number(const char *str, long *result);

#endif //MS_BUILTIN_H
