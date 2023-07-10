#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

static bool	is_argv_path(const char *const argv_head)
{
	if (!argv_head)
		return (false);
	if (ft_strchr_bool(argv_head, PATH_DELIMITER_CHR))
		return (true);
	return (false);
}

// PATH="path_1:path_2:path_3...:path_n"
// access(path + argv[0]) -> exec or next path
// 1. check path -> if access() return 0, exec path
//                              return -1, EACCESS, pass path -> 2
// 2. most left accessable path -> permission denied ?

// file
// search PATH
static char	*search_command_path(const char *const command, const t_var *var)
{
	char	*path;

	(void)command;
	(void)var;
	path = NULL;

	return (path);
}

static char	*create_exec_path(const char *const *argv, const t_var *var)
{
	char	*path;

	if (is_argv_path(argv[0]))
		path = x_ft_strdup(argv[0]);
	else
		path = search_command_path(argv[0], var);
	return (path);
}

static uint8_t	search_command_and_exec(char *const *argv, \
										char **environ, \
										const t_var *var)
{
	char	*exec_path;
	uint8_t	exec_status;

	if (!argv[0])
		return (-1); // todo define
	// get_path -> execve ?
	//  or
	// if (command; no slash)   -> search_path_and_exec()
	// else if (path; has slash) -> just execve()
	exec_path = create_exec_path((const char *const *)argv, var);
	exec_status = execve(exec_path, (char *const *) argv, environ);
	ft_free(&exec_path);
	return (exec_status);
}

uint8_t	execute_external_command(char *const *argv, char **environ, t_var *var)
{
	int		exec_status;

	exec_status = search_command_and_exec(argv, environ, var);
	if (!argv[0] || exec_status == EXECVE_ERROR)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", \
					SHELL_NAME, argv[0], ERROR_MSG_CMD_NOT_FOUND); // todo: tmp
	}
	return (EXIT_CODE_NO_SUCH_FILE);
}
