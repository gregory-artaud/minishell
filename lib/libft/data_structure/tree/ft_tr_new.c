#include "data_structure.h"

t_tree	*ft_tr_new(void *content, int type, int size)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->size = size;
	new->parent = NULL;
	new->branches = NULL;
	return (new);
}
