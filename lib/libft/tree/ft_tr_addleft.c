#include "tree.h"

void	ft_tr_addleft(t_tree *root, t_tree *left)
{
	ft_lstadd_front(&(root->branches), ft_lstnew(left));
}
