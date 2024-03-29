#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_string.h"

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

static t_result	add_pattern_matched_files(const char *token_str, \
											const bool *is_quoted_arr, \
											t_deque *matched_filenames)
{
	DIR				*dirp;
	struct dirent	*dirent;
	t_result		result;

	if (open_current_directory(&dirp) == PROCESS_ERROR)
	{
		close_current_directory(dirp);
		return (PROCESS_ERROR);
	}
	while (true)
	{
		result = get_next_dirp_in_current(dirp, &dirent);
		if (result == PROCESS_ERROR)
		{
			close_current_directory(dirp);
			return (PROCESS_ERROR);
		}
		if (result == BREAK)
			break ;
		if (!is_hidden_file(token_str) && is_hidden_file(dirent->d_name))
			continue ;
		add_pattern_matched_filename_each(\
				token_str, dirent->d_name, is_quoted_arr, matched_filenames);
	}
	return (close_current_directory(dirp));
}

// * -> [libft],[srcs],[includes]..
// in* -> [input.c],[in1],[includes]..
t_deque	*get_pattern_matched_filenames(const t_token *token, t_result *result)
{
	t_deque		*matched_filenames;
	const char	*str = token->str;
	const bool	*is_quoted_arr = token->is_quoted_arr;

	matched_filenames = deque_new();
	if (!matched_filenames)
		ft_abort();
	*result = add_pattern_matched_files(str, is_quoted_arr, matched_filenames);
	if (*result == PROCESS_ERROR)
	{
		deque_clear_all(&matched_filenames, del_token);
		return (NULL);
	}
	sort_filenames(matched_filenames);
	// debug_token_dq(matched_filenames, __func__);
	return (matched_filenames);
}
