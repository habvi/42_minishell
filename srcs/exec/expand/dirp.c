#include <errno.h>
#include <sys/types.h>
#include "minishell.h"
#include "ms_expansion.h"
#include "ft_sys.h"

// not use x_opendir because not all error return PROCESS_ERROR.
t_result	open_current_directory(DIR **dirp)
{
	errno = 0;
	*dirp = opendir(CURRENT_DIR);
	if (!*dirp)
	{
		if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
			return (CONTINUE);
		perror("opendir");
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

// error: only EBADF. just return NULL and go to next.
// not use x_readdir. last return NULL and that is success.
t_result	get_next_dirp_in_current(DIR *dirp, struct dirent **dirent)
{
	errno = 0;
	*dirent = readdir(dirp);
	if (!*dirent)
	{
		if (errno)
		{
			perror("readdir");
			return (PROCESS_ERROR);
		}
		return (BREAK);
	}
	return (CONTINUE);
}

t_result	close_current_directory(DIR *dirp)
{
	if (x_closedir(dirp) == CLOSEDIR_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
