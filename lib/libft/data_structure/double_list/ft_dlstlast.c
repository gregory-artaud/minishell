#include "data_structure.h"

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	t_dlist	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}
