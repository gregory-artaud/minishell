#include "tree.h"

int	ft_tr_brsize(t_tree *tr)
{
	if (!tr)
		return (0);
	return (ft_lstsize(tr->branches));
}
