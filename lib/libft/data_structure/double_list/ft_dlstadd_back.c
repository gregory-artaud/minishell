#include "data_structure.h"

void	ft_dlstadd_back(t_dlist **alst, t_dlist *new)
{
	t_dlist	*maillon;

	if (*alst == 0)
		*alst = new;
	else
	{
		maillon = *alst;
		while (maillon->next != 0)
			maillon = maillon->next;
		maillon->next = new;
		new->previous = maillon;
	}
}
