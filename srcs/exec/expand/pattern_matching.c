#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_result.h"
#include "ft_deque.h"
#include "ft_string.h"

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
		new_node = create_token_node(dup_filename, '\0'); // todo: next_chr
		deque_add_back(matched_filenames, new_node);
	}
}

// error: only EBADF. just return NULL and go to next.
static t_result	get_next_dirp_in_current(DIR *dirp, struct dirent **dirent)
{
	errno = 0;
	*dirent = readdir(dirp);
	if (!*dirent)
	{
		if (errno)
			return (PROCESS_ERROR); // todo: print error
		return (BREAK);
	}
	return (CONTINUE);
}

// todo: return t_result?
static void	add_pattern_matched_filenames(const char *token_str, \
											const bool *is_quoted_arr, \
											t_deque *matched_filenames)
{
	DIR				*dirp;
	struct dirent	*dirent;
	t_result		result;

	// continue: EACCES,ENOENT,ENOTDIR. other : return PROCRSS_ERROR exit
	dirp = opendir(CURRENT_DIR);
	if (!dirp) // todo: error
		return ;
	while (true)
	{
		result = get_next_dirp_in_current(dirp, &dirent);
		if (result == PROCESS_ERROR) // return PROCRSS_ERROR exit minishell
		{
			// todo: error handle.
			continue ;
		}
		if (result == BREAK)
			break ;
		// printf("[%hhu], %s\n", dirent->d_type, dirent->d_name);
		add_pattern_matched_filename_each(\
				token_str, dirent->d_name, is_quoted_arr, matched_filenames);
	}
	closedir(dirp); // todo: return PROCRSS_ERROR exit minishell
}

// * -> [libft],[srcs],[includes]..
// in* -> [input.c],[in1],[includes]..
t_deque	*get_pattern_matched_filenames(t_token *token)
{
	t_deque		*matched_filenames;
	const char	*str = token->str;
	const bool	*is_quoted_arr = token->is_quoted_arr;

	matched_filenames = deque_new();
	if (!matched_filenames)
		ft_abort();
	// if (dot)
		//
	// else  result
	add_pattern_matched_filenames(str, is_quoted_arr, matched_filenames);
	// sort(matched_filenames);
	// debug_token_dq(matched_filenames, __func__);
	return (matched_filenames);
}
