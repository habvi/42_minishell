#include "ms_tokenize.h"
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
