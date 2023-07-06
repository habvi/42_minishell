#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

void	execute_heredoc_command_leaf(t_ast *ast_node)
{
	(void)ast_node;
	// command & redirect -> redirect
	// filename
	// open
	// exec heredoc
	// next, unlink
}

void	execute_heredoc_subshell_node(t_ast	*ast_node)
{
	(void)ast_node;
	// redirect -> redirect
	// filename
	// open
	// exec heredoc
	// next, unlink
}
