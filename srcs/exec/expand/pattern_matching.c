#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_result.h"
#include "ft_deque.h"

static void	add_pattern_matched_filename_each(const char *token_str, const char *filename, t_deque *matched_filenames)
{
	bool			is_matched_filename;
	char			*dup_filename;
	t_deque_node	*new_node;

	is_matched_filename = is_pattern_match_target_path(token_str, filename);
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
			return (PROCESS_ERROR); // todo: print error?
		return (FAILURE);
	}
	return (CONTINUE);
}

// todo: return t_result?
static void	add_pattern_matched_filenames(const char *token_str, t_deque *matched_filenames)
{
	DIR 			*dirp;
	struct dirent	*dirent;
	t_result		result;
	// t_deque_node	*new_node;

	dirp = opendir(CURRENT_DIR);
	if (!dirp)
		return ; // todo: error
	while (true)
	{
		result = get_next_dirp_in_current(dirp, &dirent);
		if (result == PROCESS_ERROR)
		{
			// new_node = create_token_node(token_str, '\0'); // todo: error handle. add or not add
			// deque_add_back(matched_tokens, new_node);
			continue ;
		}
		if (result == FAILURE)
			break ;
		// printf("[%hhu], %s\n", dirent->d_type, dirent->d_name);
		add_pattern_matched_filename_each(token_str, dirent->d_name, matched_filenames);
	}
	closedir(dirp); // todo: error
}

// * -> [libft],[srcs],[includes]..
// in* -> [input.c],[in1],[includes]..
t_deque	*get_pattern_matched_filenames(const char *token_str)
{
	t_deque	*matched_filenames;

	matched_filenames = deque_new();
	if (!matched_filenames)
		ft_abort();
	add_pattern_matched_filenames(token_str, matched_filenames);
	// sort(matched_filenames);
	// debug_token_dq(matched_filenames, __func__);
	return (matched_filenames);
}
