#include "data_structure.h"

void	ft_dlstdelone(t_dlist *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
	return ;
}
