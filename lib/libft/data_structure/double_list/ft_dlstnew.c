#include "data_structure.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}
