#include "tree.h"

t_tree	*ft_tr_leftchild(t_tree *tr)
{
	if (!tr || !tr->branches)
		return (NULL);
	return ((t_tree *)tr->branches->content);
}
