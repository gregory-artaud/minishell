#include "tree.h"

t_list	*get_node(t_tree *tr)
{
	t_list	*node;

	node = tr->parent->branches;
	while (node && (t_tree *)node->content != tr)
		node = node->next;
	return (node);
}

t_tree	*ft_tr_next_sibling(t_tree *tr)
{
	t_list	*node;

	if (!tr || !tr->parent)
		return (NULL);
	node = get_node(tr)->next;
	if (!node)
		return (NULL);
	return ((t_tree *)node->content);
}
