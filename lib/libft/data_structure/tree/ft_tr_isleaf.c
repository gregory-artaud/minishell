#include "data_structure.h"

int	ft_tr_isleaf(t_tree *tr)
{
	if (!tr)
		return (0);
	return (!tr->branches);
}
