#include "tree.h"

int		ft_tr_isleaf(t_tree *tr)
{
	return (!tr->branches);
}
