#include "data_structure.h"

int	ft_dlstsize(t_dlist *lst)
{
	unsigned int	i;
	t_dlist			*current;

	if (!lst)
		return (0);
	current = lst->next;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i + 1);
}
