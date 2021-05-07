#include "minishell.h"

int	fill_arg(t_shell *sh, t_tree *tree, t_token *token)
{
	char	**arg;
	int		nb_arg;
	int		i;

	nb_arg = ft_nb_arg(*sh, token);
	arg = malloc(sizeof(char *) * nb_arg);
	if (arg == NULL)
		return (MALLOC_BREAK);
	i = 0;
	while (i < nb_arg)
	{
		token = sh->tokens->content;
		arg[i] = malloc(sizeof(char) * (ft_strlen(token->value) + 1));
		ft_strncpy(arg[i], token->value, ft_strlen(token->value));
		i++;
		sh->tokens = sh->tokens->next;
	}
	ft_tr_addleft(tree, ft_tr_new(arg, token->type, i));
	return (1);
}

void	ft_fill_sep(t_shell sh, t_tree *tree)
{
	t_token	*token;
	t_tree	*new;

	while (sh.tokens)
	{
		token = sh.tokens->content;
		if (token->type == SEPARATOR)
		{
			if (tree->content == NULL)
			{
				tree->content = token->value;
				tree->type = token->type;
			}
			else
			{
				new = ft_tr_new(token->value, token->type, 0);
				ft_tr_addright(tree, new);
				tree = new;
			}
		}
		sh.tokens = sh.tokens->next;
	}
}

int	fill_exec(t_token *token, t_tree **tree)
{
	if (token->type == EXECUTABLE)
	{
		if ((*tree)->content != NULL)
		{
			fill_new_branche(token, tree);
		}
		else
		{
			(*tree)->content = token->value;
			(*tree)->type = token->type;
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
		ft_strncpy(redirec[0], token->value, ft_strlen(token->value));
		sh->tokens = sh->tokens->next;
		token = sh->tokens->content;
		redirec[1] = malloc(sizeof(char) * ft_strlen(token->value) + 1);
		ft_strncpy(redirec[1], token->value, ft_strlen(token->value));
		ft_tr_addright(*tree, ft_tr_new(redirec, token->type, 2));
		sh->tokens = sh->tokens->next;
	}
}

int	fill_cmd(t_shell *sh, t_tree *tree, t_list **tk)
{
	t_token	*token;

	token = (*tk)->content;
	if (token->type == SEPARATOR)
		*tk = (*tk)->next;
	token = (*tk)->content;
	if (fill_exec(token, &tree))
		return (EXIT_FAILURE);
	*tk = (*tk)->next;
	if (*tk)
		token = (*tk)->content;
	if (token->type == ARGUMENT)
		fill_arg(sh, tree, token);
	fill_redirect(sh, &tree);
	return (EXIT_SUCCESS);
}
