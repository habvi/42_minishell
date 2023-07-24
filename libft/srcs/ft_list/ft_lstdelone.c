#include "ft_list.h"
#include "ft_mem.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	if (del)
		del(lst->content);
	ft_free((void **)&lst);
}
