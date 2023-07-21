#include "minishell.h"
#include "ft_string.h"
#include "ft_mem.h"

static char	*add_tail_slash_to_path(char *path)
{
	const size_t	len = ft_strlen(path);
	char			*new_path;

	if (len == 0)
		new_path = x_ft_strdup(STR_CURRENT_PATH);
	else if (path[len - 1] == CHR_SLASH)
		new_path = x_ft_strdup(path);
	else
		new_path = x_ft_strjoin(path, STR_SLASH);
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
	if (*head == CHR_PATH_DELIMITER)
	{
		*path_list = head + 1;
		return (x_ft_strdup(EMPTY_STR));
	}
	tail = head;
	while (*tail && *tail != CHR_PATH_DELIMITER)
		tail++;
	path = x_ft_strndup(head, tail - head);
	if (*tail)
		tail++;
	*path_list = tail;
	new_path = add_tail_slash_to_path(path);
	ft_free(&path);
	return (new_path);
}
