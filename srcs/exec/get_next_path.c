#include "minishell.h"
#include "ft_string.h"
#include "ft_mem.h"

static char	*add_tail_slash_to_path(char *path)
{
	const size_t	len = ft_strlen(path);
	char			*new_path;

	if (len == 0)
		new_path = x_ft_strdup("./");
	else if (path[len - 1] == '/')
		new_path = x_ft_strdup(path);
	else
		new_path = x_ft_strjoin(path, "/");
	return (new_path);
}

// need [path + ":"]
// "" -> "."
char	*get_next_path(char **path_list)
{
	char	*path;
	char	*head;
	char	*tail;
	char	*new_path;

	head = *path_list;
	if (*head == ':')
	{
		*path_list = head + 1;
		return (x_ft_strdup(""));
	}
	tail = head;
	while (*tail && *tail != ':')
		tail++;
	path = ft_strndup(head, tail - head); // todo: x_
	if (*tail)
		tail++;
	*path_list = tail;
	new_path = add_tail_slash_to_path(path);
	ft_free(&path);
	return (new_path);
}
