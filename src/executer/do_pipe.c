#include "minishell.h"

int	has_output_redirect(t_tree *tr)
{
	(void)tr;
	return (1);
}

int	has_input_redirect(t_tree *tr)
{
	(void)tr;
	return (1);
}

t_tree	*get_right(t_tree *tr)
{
	t_tree	*r;

	r = ft_tr_leftchild(tr);
	r = ft_tr_next_sibling(r);
	if (!r)
		return (NULL);
	if (r->type == SEPARATOR)
		r = ft_tr_leftchild(r);
	
}

int	do_pipe(t_tree *tr)
{
	t_tree	*left;
	t_tree	*right;

	left = ft_tr_leftchild(tr);
	right = get_right(tr);
	if (!left || !right)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	return (!(has_output_redirect(left) || has_input_redirect(right)));
}
