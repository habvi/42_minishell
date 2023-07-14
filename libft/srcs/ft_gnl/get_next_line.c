#include "ft_gnl_inter.h"

static bool	is_new_line(char *str)
{
	if (str == NULL)
		return (false);
	while (*str)
	{
		if (*str == LF)
			return (true);
		str++;
	}
	return (false);
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

static char	*read_buf(char **saved, int fd, bool *finish_read)
{
	char	*buf;
	ssize_t	read_ret;

	buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	read_ret = read(fd, buf, BUFFER_SIZE);
	if (read_ret == GNL_READ_ERROR)
		return (ft_free_for_gnl(saved, buf));
	buf[read_ret] = '\0';
	if (!read_ret)
		*finish_read = true;
	return (buf);
}

static char	*output(char **saved)
{
	char	*ps;
	char	*left;
	char	*tail;

	ps = *saved;
	if (ps == NULL || *ps == '\0')
		return (ft_free_for_gnl(saved, NULL));
	while (*ps && *ps != LF)
		ps++;
	left = ft_substr_for_gnl(*saved, 0, ps - *saved + 1);
	if (left == NULL)
		return (ft_free_for_gnl(saved, NULL));
	if (*left == '\0')
		return (ft_free_for_gnl(saved, left));
	tail = ps;
	while (*tail)
		tail++;
	if (*ps == LF)
		ps++;
	*saved = ft_memmove_for_gnl(*saved, ps, tail - ps + 1);
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*saved = NULL;
	bool		finish_read;
	char		*buf;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	finish_read = false;
	while (!finish_read)
	{
		if (is_new_line(saved))
			break ;
		buf = read_buf(&saved, fd, &finish_read);
		if (buf == NULL)
			return (ft_free_for_gnl(&saved, NULL));
		tmp = ft_strjoin(saved, buf);
		ft_free_for_gnl(&saved, buf);
		if (tmp == NULL)
			return (NULL);
		saved = tmp;
	}
	return (output(&saved));
}
