#include "minishell.h"

int	has_output_redirect(t_tree *tr)
{
	if(tr->type != EXECUTABLE)
		return (1);
		tr = ft_tr_next_sibling(ft_tr_leftchild(tr));
	if (!tr)
		return (0);
	return (is_in((char **)tr->content, ">>")
			|| is_in((char **)tr->content, ">"));
}

int	do_pipe(t_tree *tr)
{
	t_tree	*tmp;

	tmp = ft_tr_leftchild(tr);
	if (!tmp)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	if (has_output_redirect(tmp))
		return (0);
	tmp = ft_tr_next_sibling(tmp);
	if (!tmp)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	tmp = ft_tr_leftchild(tmp);
	if (has_input_redirect(tmp))
		return (0);
	return (1);
}
