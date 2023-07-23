#include "minishell.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

static bool	is_new_line(char *str)
{
	if (!str)
		return (false);
	return (ft_strchr_bool(str, LF));
}

static void	*ft_free_for_gnl(char **saved, char *ps)
{
	if (*saved != NULL)
	{
		free(*saved);
		*saved = NULL;
	}
	if (ps != NULL)
		free(ps);
	return (NULL);
}

static char	*read_buf(char **saved, int fd, bool *finish_read, t_result *result)
{
	char	*buf;
	ssize_t	read_ret;

	buf = (char *)x_malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		ft_abort();
	read_ret = read(fd, buf, BUFFER_SIZE);
	if (read_ret == READ_ERROR)
	{
		*result = PROCESS_ERROR;
		return (ft_free_for_gnl(saved, buf));
	}
	buf[read_ret] = CHR_NULL;
	if (!read_ret)
		*finish_read = true;
	return (buf);
}

static char	*create_one_line(char **saved)
{
	char	*ps;
	char	*left;
	char	*tail;

	ps = *saved;
	if (ps == NULL || *ps == CHR_NULL)
		return (ft_free_for_gnl(saved, NULL));
	while (*ps && *ps != LF)
		ps++;
	left = x_ft_strndup(*saved, ps - *saved + 1);
	if (!left)
		return (ft_free_for_gnl(saved, NULL));
	if (*left == CHR_NULL)
		return (ft_free_for_gnl(saved, left));
	tail = ps;
	while (*tail)
		tail++;
	if (*ps == LF)
		ps++;
	*saved = ft_memmove(*saved, ps, tail - ps + 1);
	return (left);
}

char	*ft_get_next_line(int fd, t_result *result)
{
	static char	*saved = NULL;
	bool		finish_read;
	char		*buf;
	char		*tmp;

	finish_read = false;
	while (!finish_read)
	{
		if (is_new_line(saved))
			break ;
		buf = read_buf(&saved, fd, &finish_read, result);
		if (!buf)
			return (ft_free_for_gnl(&saved, NULL));
		tmp = x_ft_strjoin(saved, buf);
		ft_free_for_gnl(&saved, buf);
		saved = tmp;
	}
	return (create_one_line(&saved));
}
