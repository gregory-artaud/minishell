#include "tree.h"

void	ft_tr_addright(t_tree *root, t_tree *right)
{
	ft_lstadd_back(&(root->branches), ft_lstnew(right));
}
