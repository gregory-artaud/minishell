#include "minishell.h"

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

void	ft_fill_sep(t_tree **tree, char *sep)
{
	t_tree	*new;

	if ((*tree)->content == NULL)
		(*tree)->content = sep;
	else
	{
		new = ft_tr_new(sep);
		ft_tr_addright(*tree, new);
		*tree = new;
	}
}

void    ft_verif_sep(t_tree **tree, t_shell sh)
{
    t_token *token;

    if (sh.tokens)
        token = sh.tokens->content;
    while (sh.tokens && token->type != SEPARATOR)
    {
        sh.tokens = sh.tokens->next;
        if (sh.tokens)
            token = sh.tokens->content;
    }
    if (token->type == SEPARATOR)
        ft_fill_sep(tree, token->value);
}

void	fill_new_branche(t_token *token, t_tree **tree)
{
	t_tree		*new;

	if ((*tree)->branches == NULL)
	{
		ft_tr_addleft(*tree, ft_tr_new(token->value));
		(*tree) = (*tree)->branches->content;
	}
	else
	{
		new = ft_tr_new(token->value);
		ft_tr_addright(*tree, new);
		(*tree) = new;
	}
}

int	fill_exec(t_token *token, t_tree **tree)
{
	if (token->type == EXECUTABLE)
	{
		if (!(ft_verif_builtin(token->value)))
		{
			if ((*tree)->content != NULL)
				fill_new_branche(token, tree);
			else
				(*tree)->content = token->value;
		}
		else
		{
			ft_errorzsh(token->value);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	fill_redirect(t_shell *sh, t_tree **tree)
{
	t_token	*token;
	char	**redirec;

	if (sh->tokens)
		token = sh->tokens->content;
	if (sh->tokens && token->type == REDIRECT)
	{
		redirec = malloc(sizeof(char *) * 2);
		redirec[0] = malloc(sizeof(char) * ft_strlen(token->value) + 1);
		redirec[0] = token->value;
		sh->tokens = sh->tokens->next;
		token = sh->tokens->content;
		redirec[1] = malloc(sizeof(char) * ft_strlen(token->value) + 1);
		redirec[1] = token->value;
		ft_tr_addright(*tree, ft_tr_new(redirec));
		sh->tokens = sh->tokens->next;
	}
}

int	fill_cmd(t_shell *sh, t_tree *tree)
{
	t_token		*token;

    ft_verif_sep(&tree, *sh);
	token = sh->tokens->content;
	if (token->type == SEPARATOR)
		sh->tokens = sh->tokens->next;
	token = sh->tokens->content;
	if (fill_exec(token, &tree))
        return (EXIT_FAILURE);
	sh->tokens = sh->tokens->next;
	if (sh->tokens)
		token = sh->tokens->content;
	if (token->type == ARGUMENT)
		fill_arg(sh, tree, token, tree->content);
	fill_redirect(sh, &tree);
	return (EXIT_SUCCESS);
}
