#include <limits.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ft_dprintf.h"
#include "ft_hash.h"
#include "ft_sys.h"
#include "ft_mem.h"

static int	count_up_seed_num(void)
{
	static int	num;

	num++;
	return (num);
}

static char	*create_hidden_filename(const char *hash_str, const char *seed_str)
{
	char	*filename;
	char	*hidden_filename;

	filename = x_ft_strjoin(hash_str, seed_str);
	hidden_filename = x_ft_strjoin(HEREDOC_FILE_PREFIX, filename);
	ft_free(&filename);
	return (hidden_filename);
}

static char	*create_hidden_filename_based_on_hash(void)
{
	const int	seed = count_up_seed_num();
	size_t		hash;
	char		*seed_str;
	char		*hash_str;
	char		*hidden_filename;

	seed_str = x_ft_itoa(seed);
	hash = hs_gen_fnv((const unsigned char *)seed_str, (size_t)INT_MAX);
	hash_str = x_ft_itoa((int)hash);
	hidden_filename = create_hidden_filename(hash_str, seed_str);
	ft_free(&seed_str);
	ft_free(&hash_str);
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

// filename = <hash> + num -> itoa
char	*create_heredoc_filename(void)
{
	char	*filename;

	while (true)
	{
		filename = create_hidden_filename_based_on_hash();
		if (is_file_creatable(filename))
			break ;
		ft_free(&filename);
	}
	return (filename);
}
