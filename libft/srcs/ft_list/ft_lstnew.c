#include "ft_list.h"
#include "ft_sys.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list *)x_malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
