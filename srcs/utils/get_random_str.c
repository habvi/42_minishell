#include <fcntl.h>
#include <string.h>
#include "minishell.h"
#include "ft_ascii.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

// 01234567
// abc?ef?
//        ^
// ^
static char	read_random_alnum(const int fd)
{
	static ssize_t	i = 0;
	static char		buf[RANDOM_BUF_SIZE + 1];
	ssize_t			read_size;

	read_size = RANDOM_BUF_SIZE;
	while (true)
	{
		if (i == 0)
		{
			read_size = read(fd, buf, RANDOM_BUF_SIZE);
			if (read_size == -1)
				return (CHR_NULL);
		}
		while (i < read_size && !ft_isalnum((int)buf[i]))
			i++;
		if (i == read_size)
			i = 0;
		else
			break ;
	}
	return (buf[i++]);
}

static char	*read_random_str(const int fd, const size_t size)
{
	char	*buf;
	size_t	i;

	buf = (char *)x_malloc(sizeof(char) * (size + 1));
	if (!buf)
		ft_abort();
	i = 0;
	while (i < size)
	{
		buf[i] = read_random_alnum(fd);
		if (!buf[i])
			return (ft_free(&buf));
		i++;
	}
	buf[size] = '\0';
	return (buf);
}

char	*get_random_str(const size_t size)
{
	int		fd;
	char	*random_str;

	errno = 0;
	fd = x_open(RANDOM_FILENAME, O_RDONLY);
	if (fd == -1)
	{
		strerror(errno); // todo: tmp
		return (NULL);
	}
	random_str = read_random_str(fd, size);
	close(fd); // todo: error...?
	if (!random_str)
		return (NULL);
	return (random_str);
}
