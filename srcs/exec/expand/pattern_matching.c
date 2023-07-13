#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include "minishell.h"
// #include "ms_builtin.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_result.h"
#include "ft_deque.h"
// #include "ft_mem.h"
// #include "ft_string.h"

static void	pattern_matching_each(const char *token_str, const char *filename, t_deque *matched_tokens)
{
	// t_deque_node	*new_node;
	// char			*dup_filename;

	(void)token_str;
	(void)filename;
	(void)matched_tokens;
	// longest_common_subsequence(token_str, filename);
	// if ok
	// dup_filename = x_ft_strdup(filename);
	// new_node = create_token_node(dup_filename, '\0'); // todo: next_chr
	// deque_add_back(matched_tokens, new_node);
	return ;
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

// * -> [libft],[srcs],[includes]..
// in* -> [input.c],[in1],[includes]..
void	pattern_matching_and_add(const char *token_str, t_deque *matched_tokens)
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
			// new_node = create_token_node(token_str, '\0'); // todo: next_chr
			// deque_add_back(matched_tokens, new_node);
			continue ;
		}
		if (result == FAILURE)
			break ;
		printf("[%hhu], %s\n", dirent->d_type, dirent->d_name);
		pattern_matching_each(token_str, dirent->d_name, matched_tokens);
	}
	debug_token_dq(matched_tokens, __func__);
	closedir(dirp); // todo: error
}
