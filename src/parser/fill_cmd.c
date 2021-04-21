#include "minishell.h"

int	fill_separator(t_shell sh, t_tree *tree)
{
	t_token	*token;
	int		i;

	i = 1;
	while (sh.tokens)
	{
		token = sh.tokens->content;
		if (token->type == SEPARATOR)
		{
			if (tree->content == NULL)
				tree->content = token->value;
			else
				ft_tr_addright(tree, ft_tr_new(token->value));
			i++;
		}
		sh.tokens = sh.tokens->next;
	}
	return (i);
}

int	ft_nb_arg(t_shell sh, t_token *token)
{
	int	i;

	i = 0;
	while (token->type == ARGUMENT && sh.tokens)
	{
		i++;
		sh.tokens = sh.tokens->next;
		token = sh.tokens->content;
	}
	return (i);
}

int	fill_arg(t_shell *sh, t_tree *tree, t_token *token, char *charset)
{
	char	**arg;
	int		nb_arg;
	int		i;
	char	c;

	c = *charset;
    if (c != ';' && c != '|')
        c = ';';
	nb_arg = ft_nb_arg(*sh, token);
	arg = malloc(sizeof(char *) * nb_arg);
	if (arg == NULL)
		return (MALLOC_BREAK);
	i = 0;
	while (i < nb_arg)
	{
		token = sh->tokens->content;
		arg[i] = malloc(sizeof(char) * (ft_strlen_sp(token->value, c) + 1));
		arg[i] = token->value;
		i++;
		sh->tokens = sh->tokens->next;
	}
	ft_tr_addleft(tree, ft_tr_new(arg));
	return (1);
}

int	fill_cmd(t_shell *sh, t_tree *tree)
{
	t_token	*token;

	token = sh->tokens->content;
	if (token->type == EXECUTABLE)
	{
		if (!(ft_verif_builtin(token->value, tree->content)))
		{
			if (tree->content != NULL)
			{
				ft_tr_addleft(tree, ft_tr_new(token->value));
				tree = tree->branches->content;
			}
			else
				tree->content = token->value;
		}
		else
		{
			ft_errorzsh(token->value);
			return (EXIT_FAILURE);
		}
	}
	sh->tokens = sh->tokens->next;
	if (sh->tokens)
		token = sh->tokens->content;
	if (token->type == ARGUMENT)
		fill_arg(sh, tree, token, tree->content);
	return (EXIT_SUCCESS);
}
