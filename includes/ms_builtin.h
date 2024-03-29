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

# define CHDIR			"chdir"

/* option */
# define CMD_OPTION_MARKER				'-'
# define CMD_OPTION_MARKER_STR			"-"
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
// error in norm 3.3.51 ...
// # define PATH_DOUBLE_SLASH	"//"
# define PATH_DOT			"."
# define PATH_DOT_DOT		".."
# define CHAR_PATH_DOT		'.'
# define PATH_CURRENT		"."

# define VAR_PRINT_QUOTE	"\""

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

/* ft_cd */
// cd
char		*cd_set_path(const char *arg, t_var *var, bool *is_print_path);
t_result	cd_exec_chdir(const char *path, int *tmp_err);
char		*cd_create_path_with_pwd(const char *arg, \
										const char *path, \
										const char *internal_pwd, \
										t_result *result);
t_result	chack_is_valid_directory(const char *arg, \
										const char *path, \
										char *new_path, \
										const bool is_contain_dot);
t_result	cd_check_current_exist(const char *internal_pwd);
t_result	cd_check_new_path_exist(const char *arg, \
									char **new_path, \
									const char *path, \
									const char *internal_pwd);
void		set_absolute_path_in_error(char **absolute_path, \
										const char *backup_pwd, \
										const char *path, \
										t_result result);
void		cd_update_pwd(char *path, t_context *context);
// canonicalize
char		*cd_canonicalize_path(const char *internal_pwd, const char *path);
t_deque		*allocate_path_elems(void);
bool		is_internal_pwd_relative(const char *internal_pwd);
bool		is_head_double_slash(const char *path);
void		del_path_elem(void *content);
void		destroy_path_elems(t_deque **path_elems);
t_deque		*separate_path_and_join(const char *path, \
									const char *internal_pwd, \
									t_deque *path_elems);
void		add_split_path_elems(t_deque *path_elems, const char *path);
void		erase_dot_path_for_relative(t_deque **path_elems);
void		erase_dot_path(t_deque **path_elems);
void		erase_dot_dot_path(t_deque **path_elems);
char		*convert_path_elems_to_path(t_deque *path_elems, \
										const char *internal_pwd);
char		*search_cdpath(const char *arg, t_var *var, bool *is_print_path);

bool		is_absolute_path(const char *path);

#endif //MS_BUILTIN_H
