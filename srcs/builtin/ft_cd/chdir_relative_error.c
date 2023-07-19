#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"

void	set_absolute_path_in_error(char **absolute_path, \
									const char *backup_pwd, \
									const char *path, \
									t_result result)
{
	ft_free(absolute_path);
	if (result == FAILURE)
		*absolute_path = x_ft_strdup(backup_pwd);
	else if (result == BREAK) //todo only . & .. can join
	{
		*absolute_path = x_ft_strjoin(backup_pwd, PATH_DELIMITER_STR);
		*absolute_path = extend_str(*absolute_path, x_ft_strdup(path));
	}
}

void	restore_path_and_clean_up(const char *backup_pwd, \
									char **canonicalized_path, \
									t_deque **path_elems)
{
	int	tmp_err;

	cd_exec_chdir(backup_pwd, &tmp_err);
	ft_free(canonicalized_path);
	deque_clear_all(path_elems, del_path_elem);
}
