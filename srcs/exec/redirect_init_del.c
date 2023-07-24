#include "minishell.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"

t_redirect	*init_redirect(void)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)x_malloc(sizeof(t_redirect) * 1);
	if (!redirect)
		ft_abort();
	redirect->kind = TOKEN_KIND_WORD;
	redirect->tokens = deque_new();
	if (!redirect->tokens)
		ft_abort();
	redirect->heredoc_filename = NULL;
	return (redirect);
}

void	del_redirect(void *content)
{
	t_redirect	*redirect;

	if (!content)
		return ;
	redirect = (t_redirect *)content;
	deque_clear_all(&redirect->tokens, del_token);
	if (redirect->heredoc_filename)
	{
		unlink(redirect->heredoc_filename);
		ft_free((void **)&redirect->heredoc_filename);
	}
	ft_free((void **)&redirect);
}
