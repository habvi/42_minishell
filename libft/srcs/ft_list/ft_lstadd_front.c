#include "ft_list.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst)
		ft_lstlast(new)->next = *lst;
	*lst = new;
}
