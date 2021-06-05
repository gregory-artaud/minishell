#include "minishell.h"

int	has_output_redirect(t_tree *tr)
{
	t_tree	*red;
	int		i;
	char	**s;

	red = ft_tr_next_sibling(ft_tr_leftchild(tr));
	if (!red || red->type != REDIRECT)
		return (0);
	s = (char **)red->content;
	i = -1;
	while (++i < red->size)
		if (!ft_memcmp(s[i], REDIRECT_OUTPUT_TOKEN, R_O_T_LEN + 1)
			|| !ft_memcmp(s[i], REDIRECT_OUTPUT_APPEND_TOKEN, R_O_A_T_LEN + 1))
			return (1);
	return (0);
}

int	has_input_redirect(t_tree *tr)
{
	t_tree	*red;
	int		i;
	char	**s;

	red = ft_tr_next_sibling(ft_tr_leftchild(tr));
	if (!red || red->type != REDIRECT)
		return (0);
	s = (char **)red->content;
	i = -1;
	while (++i < red->size)
		if (!ft_memcmp(s[i], REDIRECT_INPUT_TOKEN, R_I_T_LEN + 1))
			return (1);
	return (0);
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
	return (r);
}

int	do_pipe(t_tree *tr)
{
	t_tree	*left;
	t_tree	*right;

	left = ft_tr_leftchild(tr);
	right = get_right(tr);
	if (!left || !ft_strlen(left->content)
		|| !right || !ft_strlen(right->content))
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	return (!(has_output_redirect(left) || has_input_redirect(right)));
}
