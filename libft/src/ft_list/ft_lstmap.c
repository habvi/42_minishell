#include "ft_list.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*res;

	if (lst == NULL)
		return (NULL);
	res = NULL;
	while (lst)
	{
		if (f)
			tmp = ft_lstnew(f(lst->content));
		else
			tmp = ft_lstnew(lst->content);
		if (tmp == NULL)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, tmp);
		lst = lst->next;
	}
	return (res);
}
