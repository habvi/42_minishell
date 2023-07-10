#include <errno.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ft_mem.h"

static char	*create_hidden_filename(void)
{
	char	*random_str;
	char	*hidden_filename;

	random_str = get_random_str((size_t)RANDOM_STR_SIZE);
	if (!random_str)
		return (NULL);
	hidden_filename = x_ft_strjoin(HEREDOC_FILE_PREFIX, random_str);
	ft_free(&random_str);
	return (hidden_filename);
}

// file can create when result of access(2) is no such file
static bool	is_file_creatable(const char *filepath)
{
	int	ret;

	errno = 0;
	ret = access(filepath, F_OK);
	if (ret == ACCESS_ERROR && errno == ENOENT) //todo
		return (true);
	return (false);
}

// filename = .prefix + random_str
char	*create_heredoc_filename(void)
{
	char	*filename;

	while (true)
	{
		filename = create_hidden_filename();
		if (!filename)
			return (NULL);
		if (is_file_creatable(filename))
			break ;
		ft_free(&filename);
	}
	return (filename);
}
