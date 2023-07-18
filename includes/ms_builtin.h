#ifndef MS_BUILTIN_H
# define MS_BUILTIN_H

# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include "ms_result.h"

# define CMD_CD			"cd"
# define CMD_DECLARE	"declare"
# define CMD_ECHO		"echo"
# define CMD_ENV		"env"
# define CMD_EXIT		"exit"
# define CMD_EXPORT		"export"
# define CMD_PWD		"pwd"
# define CMD_UNSET		"unset"

/* option */
# define CMD_OPTION_MARKER				'-'
# define ECHO_OPTION_DISPLAY_NEWLINE	'n'
# define DECLARE_OPTION_VAR_ENV			'x'
# define DECLARE_DEL_ATTR_MARKER		'+'
# define DECLARE_OPTION_DISPLAY_ATTR	'p'

# define ECHO_SEPARATOR		' '
# define END_OF_CMD_OPTION	"--"

# define CD_ARG_HOME		"~"
# define CD_ARG_OLDPWD		"-"
# define ABSOLUTE_PATH_HEAD	'/'
# define PATH_DELIMITER_CHR	'/'
# define PATH_DELIMITER_STR	"/"
# define PATH_DOT			"."
# define PATH_DOT_DOT		".."
# define CHAR_PATH_DOT		'.'
# define PATH_CURRENT		"."

# define VAR_PRINT_QUOTE	"\""

// todo: naming...
# define EXIT_ONLY_CMD_CNT		1
# define EXIT_ARG_IDX			1
# define VALID_ARG_CNT			2

# define NON_NUMERIC_ARG_STATUS	2
# define TOO_MANY_ARG_STATUS	1
# define ENV_INVALID_OPTION		125

# define NOT_A_VALID_IDENTIFIER	1

# define CD_ERROR_STATUS		1

# define BYTE_MASK				(0xFF)

# define ERROR_MSG_TOO_MANY_ARG	"too many arguments"
# define ERROR_MSG_REQUIRED_NUM	"numeric argument required"
# define ERROR_MSG_INVALID_OP	"invalid option"
# define ERROR_MSG_INVALID_ARG	"invalid argument"
# define ERROR_MSG_NOT_VALID_ID	"not a valid identifier"
# define ERROR_MSG_NOT_SET		"not set"

typedef struct s_context	t_context;
typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;
typedef struct s_var		t_var;

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

uint8_t		ft_cd(const char *const *argv, t_context *context);
uint8_t		ft_declare(const char *const *argv, t_var *var);
uint8_t		ft_echo(const char *const *argv);
uint8_t		ft_env(const char *const *argv, t_var *var);
uint8_t		ft_exit(const char *const *argv, t_context *context);
uint8_t		ft_export(const char *const *argv, t_var *var);
uint8_t		ft_pwd(const char *const *argv, t_context *context);
uint8_t		ft_unset(const char *const *argv, t_var *var);

bool		is_option(const char *word, char marker);
bool		is_arg_option(const char *arg, char marker, char op_chr);
bool		is_end_of_option(const char *word);
bool		is_valid_option(const char *const *argv, \
							uint8_t *status, \
							size_t *i);
bool		skip_valid_options(const char *const *argv, \
								size_t *idx, \
								char marker, \
								char op_chr);
bool		str_to_legal_number(const char *str, long *result);
bool		is_whitespace(char c);

/* ft_cd */
// cd
char		*cd_set_path(const char *arg, t_var *var, bool *is_print_path);
t_result	cd_change_dir_to_valid_path(const char *absolute_path, \
										int *tmp_err);
void		cd_update_pwd(char *path, t_context *context);
t_result	cd_chdir_from_absolute_path(const char *path, char **absolute_path);
t_result	cd_chdir_from_relative_path(const char *arg, \
										const char *path, \
										char **absolute_path, \
										const char *internal_pwd);
// canonicalize
char		*cd_canonicalize_path(const char *path, const char *internal_pwd);
t_deque		*allocate_path_elems(void);
void		del_path_elem(void *content);
void		destroy_path_elems(t_deque *path_elems);
t_deque		*separate_path_and_join(const char *path, \
									const char *internal_pwd, \
									t_deque *path_elems);
void		split_and_add_dq(t_deque *path_elems, const char *path);
void		erase_dot_path(t_deque **dq);
void		erase_dot_dot_path(t_deque **dq);
void		handle_double_slash_path(const char *path, char **absolute_path);
char		*convert_path_elems_to_absolute_path(t_deque *path_elems);
char		*search_cdpath(const char *arg, t_var *var, bool *is_print_path);

bool		is_absolute_path(const char *path);

#endif //MS_BUILTIN_H
