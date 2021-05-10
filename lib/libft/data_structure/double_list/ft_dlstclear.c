#include "data_structure.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*next;
	t_dlist	*current;

	current = *lst;
	while (current)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
	return ;
}
