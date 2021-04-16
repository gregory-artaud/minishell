#include "tree.h"

t_tree	*ft_tr_new(void *content)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->content = content;
	new->branches = NULL;
	return (new);
}
