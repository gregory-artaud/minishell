#include "minishell.h"

int	count_separator(t_shell sh)
{
	t_token	*token;
	int		i;

	i = 0;
	while (sh.tokens)
	{
		token = sh.tokens->content;
		if (token->type == SEPARATOR)
			i++;
		sh.tokens = sh.tokens->next;
	}
	return (i);
}

int	ft_count_exec(t_shell sh)
{
	t_token	*token;
	int		i;

	i = 0;
	while (sh.tokens)
	{
		token = sh.tokens->content;
		if (token->type == EXECUTABLE)
			i++;
		sh.tokens = sh.tokens->next;
	}
	return (i);
}

void	ft_brw_token(t_shell *sh, int *nb_sep)
{
	t_token	*token;

	if (sh->tokens)
		token = sh->tokens->content;
	while (sh->tokens && token->type != SEPARATOR)
	{
		sh->tokens = sh->tokens->next;
		if (sh->tokens)
			token = sh->tokens->content;
		else
			*nb_sep = 0;
	}
}

t_tree	*fill_tree(t_shell *sh)
{
	t_tree	*root;
	t_tree	*begin;
	int		nb_sep;
	t_list	*tmp_token;

	tmp_token = sh->tokens;
	root = ft_tr_new(NULL, 5, 0);
	begin = root;
	nb_sep = ft_count_exec(*sh);
	ft_fill_sep(*sh, root);
	while (nb_sep--)
	{
		if (fill_cmd(root, &sh->tokens))
			ft_brw_token(sh, &nb_sep);
		if (root->branches)
			if (root->branches->next)
				root = root->branches->next->content;
	}
	sh->tokens = tmp_token;
	return (begin);
}

int	parser(t_shell *sh)
{
	sh->ast = fill_tree(sh);
	return (EXIT_SUCCESS);
}
