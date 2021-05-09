#include "data_structure.h"

void	ft_tr_addleft(t_tree *root, t_tree *left)
{
	if (!left || !root)
		return ;
	left->parent = root;
	ft_lstadd_front(&(root->branches), ft_lstnew(left));
}
