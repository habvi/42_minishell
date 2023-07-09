#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

void	del_token(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content;
	ft_free(&token->str);
	ft_free(&token);
}

void	*destroy_tokens(t_deque **command, void (*del)(void *))
{
	deque_clear_all(command, del);
	return (NULL);
}
