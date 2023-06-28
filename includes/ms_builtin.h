#ifndef MS_BUILTIN_H
# define MS_BUILTIN_H

# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>

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
# define END_OF_CMD_OPTION	"--"

# define CD_ARG_HOME		"~"
# define CD_ARG_OLDPWD		"-"

// todo: naming...
# define EXIT_ONLY_CMD_CNT		1
# define EXIT_ARG_IDX			1
# define VALID_ARG_CNT			2

# define NON_NUMERIC_ARG_STATUS	2
# define TOO_MANY_ARG_STATUS	1

# define NOT_A_VALID_IDENTIFIER	1
# define INVALID_OPTION			2

// cd
# define CD_NOT_SET_STATUS		1
# define CD_ERROR_STATUS		1

# define BYTE_MASK				(0xFF)

# define ERROR_MSG_TOO_MANY_ARG	"too many arguments"
# define ERROR_MSG_REQUIRED_NUM	"numeric argument required"
# define ERROR_MSG_INVALID_OP	"invalid option"
# define ERROR_MSG_NOT_VALID_ID	"not a valid identifier"

# define ERROR_MSG_NOT_SET		"not set"
# define ERROR_MSG_PERMISSION	"Permission denied"
# define ERROR_MSG_NOT_A_DIR	"Not a directory"
# define ERROR_MSG_NO_SUCH_FILE	"No such file or directory"

# define DECLARE_X				"declare -x"

typedef enum e_result		t_result;
typedef struct s_env		t_env;
typedef struct s_deque_node	t_deque_node;
typedef struct s_context	t_context;

typedef enum e_exit_argument
{
	EXIT_VALID_ARG,
	EXIT_NON_NUMERIC_ARG,
	RETURN_TOO_MANY_NUMERIC_ARG,
}	t_exit_arg;

uint8_t	ft_cd(const char *const *argv, t_context *context);
uint8_t	ft_echo(const char *const *argv);
uint8_t	ft_env(const char *const *argv, t_env *env);
uint8_t	ft_exit(const char *const *argv, t_context *context);
uint8_t	ft_export(const char *const *argv, t_env *env);
uint8_t	ft_pwd(const char *const *argv, t_context *context);
uint8_t	ft_unset(const char *const *argv, t_env *env);

// cd
char	*cd_set_path(const char *arg, t_env *env);

bool	is_option(const char *word);
bool	is_end_of_option(const char *word);
bool	is_valid_option(const char *const *argv, uint8_t *status, size_t *i);
bool	str_to_legal_number(const char *str, long *result);

#endif //MS_BUILTIN_H
