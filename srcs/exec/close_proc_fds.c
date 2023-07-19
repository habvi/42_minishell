#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_sys.h"

t_result	close_proc_in_fd(int *proc_in_fd)
{
	if (*proc_in_fd == IN_FD_INIT)
		return (SUCCESS);
	if (x_close(*proc_in_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	*proc_in_fd = IN_FD_INIT;
	return (SUCCESS);
}

t_result	close_proc_out_fd(int *proc_out_fd)
{
	if (*proc_out_fd == OUT_FD_INIT)
		return (SUCCESS);
	if (x_close(*proc_out_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	*proc_out_fd = OUT_FD_INIT;
	return (SUCCESS);
}
