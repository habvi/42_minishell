#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_result.h"
#include "ft_deque.h"
#include "ft_string.h"
#include "ft_sys.h"

// error: only EBADF. just return NULL and go to next.
static t_result	get_next_dirp_in_current(DIR *dirp, struct dirent **dirent)
{
	errno = 0;
	*dirent = x_readdir(dirp);
	if (!*dirent)
	{
		if (errno)
			return (PROCESS_ERROR);
		return (BREAK);
	}
	return (CONTINUE);
}

bool	is_hidden_file(const char *str)
{
	if (!str)
		return (false);
	return (str[0] == HIDDEN_FILE);
}

static void	add_pattern_matched_filename_each(const char *token_str, \
												const char *filename, \
												const bool *is_quoted_arr, \
												t_deque *matched_filenames)
{
	bool			is_matched_filename;
	const size_t	len_token = ft_strlen(token_str);
	char			*dup_filename;
	t_deque_node	*new_node;

	is_matched_filename = is_pattern_match_target_path(\
								token_str, len_token, filename, is_quoted_arr);
	if (is_matched_filename)
	{
		dup_filename = x_ft_strdup(filename);
		new_node = create_token_node(dup_filename, CHR_NULL);
		deque_add_back(matched_filenames, new_node);
	}
}

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

t_result	close_current_directory(DIR *dirp)
{
	if (x_closedir(dirp) == CLOSEDIR_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

static t_result	add_pattern_matched_files(const char *token_str, \
										const bool *is_quoted_arr, \
										t_deque *matched_filenames)
{
	DIR				*dirp;
	struct dirent	*dirent;
	t_result		result;

	result = open_current_directory(&dirp);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	while (true)
	{
		result = get_next_dirp_in_current(dirp, &dirent);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (result == BREAK)
			break ;
		if (!is_hidden_file(token_str) && is_hidden_file(dirent->d_name))
			continue ;
		add_pattern_matched_filename_each(\
				token_str, dirent->d_name, is_quoted_arr, matched_filenames);
	}
	result = close_current_directory(dirp);
	return (result);
}

// * -> [libft],[srcs],[includes]..
// in* -> [input.c],[in1],[includes]..
t_deque	*get_pattern_matched_filenames(t_token *token, t_result *result)
{
	t_deque		*matched_filenames;
	const char	*str = token->str;
	const bool	*is_quoted_arr = token->is_quoted_arr;

	matched_filenames = deque_new();
	if (!matched_filenames)
		ft_abort();
	*result = add_pattern_matched_files(str, is_quoted_arr, matched_filenames);
	if (*result == PROCESS_ERROR)
		return (NULL);
	sort_filenames(matched_filenames);
	// debug_token_dq(matched_filenames, __func__);
	return (matched_filenames);
}
