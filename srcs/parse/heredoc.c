#include <fcntl.h>
#include <limits.h>
#include <readline/readline.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_hash.h"
#include "ft_lib.h"
#include "ft_string.h"
#include "ft_sys.h"
#include "ft_mem.h"

static int	count_up_seed_num(void)
{
	static int	num; //todo: init value?

	num++;
	return (num);
}

static char *x_ft_itoa(int n)
{
	char	*num_str;

	num_str = ft_itoa(n);
	if (!num_str)
		ft_abort();
	return (num_str);
}

static char *x_ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
		ft_abort();
	return (join);
}

static char	*create_hidden_filename(const char *hash_str, const char *seed_str)
{
	char	*filename;
	char	*hidden_filename;

	filename = x_ft_strjoin(hash_str, seed_str);
	hidden_filename = x_ft_strjoin(HEREDOC_FILE_PREFIX, filename);
	ft_free(&filename);
	return (hidden_filename);
}

static char	*create_hidden_filename_based_on_hash(void)
{
	const int	seed = count_up_seed_num();
	size_t		hash;
	char 		*seed_str;
	char 		*hash_str;
	char 		*hidden_filename;

	seed_str = x_ft_itoa(seed);
	hash = hs_gen_fnv((const unsigned char*)seed_str, (size_t)1);
	hash_str = x_ft_itoa((int)hash);
	hidden_filename = create_hidden_filename(hash_str, seed_str);
	ft_free(&seed_str);
	ft_free(&hash_str);
	return (hidden_filename);
}

// file can create when result of access(2) is no such file
static bool	is_file_creatable(const char *filepath)
{
	int	tmp_err;
	int	ret;

	errno = 0;
	ret = access(filepath, F_OK);
	tmp_err = errno;
	if (ret == ACCESS_ERROR && tmp_err == ENOENT)
		return (true);
	return (false);
}

// filename = <hash> + num -> itoa
static char *create_heredoc_filename(void)
{
	char	*filename;

	while (true)
	{
		filename = create_hidden_filename_based_on_hash();
//		ft_dprintf(2, "try access filename:%s\n", filename);
		if (is_file_creatable(filename))
		{
//			ft_dprintf(2, " -> filename:%s\n", filename);
			break ;
		}
		ft_free(&filename);
	}
	return (filename);
}

static void	clean_up_prev_heredoc(int in_fd, char *filename)
{
	close(in_fd); 		// todo: error handling
	unlink(filename);	// todo: error handling
	ft_free(&filename);
}

// todo: error handling and msg
static t_result	open_heredoc_filedes(int *in_fd, char **filename)
{
	int	tmp_err;

	if (*in_fd != IN_FD_INIT)
		clean_up_prev_heredoc(*in_fd, *filename);
	*filename = create_heredoc_filename();
	errno = 0;
	*in_fd = open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
//	ft_dprintf(2, "new in_fd:%d, filename:%s\n", *in_fd, *filename);
	tmp_err = errno;
	if (tmp_err == ENOMEM)
	{
		perror("open");
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

static void	execute_heredoc_each(int fd, const char *delimiter)
{
	char	*line;

	rl_outstream = stderr;
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, \
			"%s: %s: %s (wanted `%s')", \
			SHELL_NAME, ERROR_TYPE_WARNING, ERROR_MSG_HEREDOC_EOF, delimiter); // todo: wanted
			break ;
		}
		if (ft_streq(line, delimiter))
		{
			ft_free(&line);
			break ;
		}
		ft_dprintf(fd, line);
		ft_dprintf(fd, "\n");
		ft_free(&line);
	}
}

static char	*get_heredoc_eof(t_deque_node *token_node)
{
	t_token	*token;

	token = (t_token *)token_node->content;
	return (token->str);
}

// todo: check filename
static t_result	execute_heredoc_all(t_redirect *redirect)
{
	t_deque_node	*token_node;
	int				in_fd;
	char			*filename;
	char 			*delimiter;
	t_result		result;

	if (!redirect)
		return (SUCCESS);
	token_node = redirect->list->node;
	in_fd = IN_FD_INIT;
	filename = NULL;
	while (token_node)
	{
		if (!is_token_kind_redirection_from_node(token_node))
		{
			token_node = token_node->next;
			continue ;
		}
		result = open_heredoc_filedes(&in_fd, &filename);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		delimiter = get_heredoc_eof(token_node->next);
		execute_heredoc_each(in_fd, delimiter);
		token_node = token_node->next;
	}
	redirect->in_fd = in_fd;
	redirect->heredoc_filename = filename;
	return (SUCCESS);
}

t_result	execute_heredoc(t_ast *ast_node)
{
	move_redirect_from_command(ast_node);
	if (execute_heredoc_all(ast_node->redirects) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
