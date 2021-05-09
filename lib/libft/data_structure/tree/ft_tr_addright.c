#include "data_structure.h"

void	ft_tr_addright(t_tree *root, t_tree *right)
{
	if (!right || !root)
		return ;
	right->parent = root;
	ft_lstadd_back(&(root->branches), ft_lstnew(right));
}
