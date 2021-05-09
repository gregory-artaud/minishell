#include "data_structure.h"

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new)
{
	new->next = *alst;
	(*alst)->previous = new;
	*alst = new;
	return ;
}
