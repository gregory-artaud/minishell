#include "minishell.h"

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

void	fill_redirect(t_tree **tree, t_list **tk)
{
	t_token	*token;
	char	**redirec;
	int		nb_redirect;
	int		i;

	nb_redirect = ft_nb_redirect(*tk);
	if (!nb_redirect)
		return ;
	redirec = ft_calloc(nb_redirect + 1, sizeof(char *));
	if (!redirec)
		return ;
	i = 0;
	while (*tk && ((t_token *)(*tk)->content)->type != SEPARATOR)
	{
		token = (*tk)->content;
		if (token->type == REDIRECT || token->type == FILE_PATH)
		{
			redirec[i] = malloc(sizeof(char) * ft_strlen(token->value) + 1);
			if (!redirec[i])
				return ;
			ft_strncpy(redirec[i++], token->value, ft_strlen(token->value));
		}
		*tk = (*tk)->next;
	}
	ft_tr_addright(*tree, ft_tr_new(redirec, REDIRECT, i));
}

int	fill_cmd(t_tree *tree, t_list **tk)
{
	t_token	*token;
	t_list	*tk_begin;

	tk_begin = *tk;
	token = (*tk)->content;
	while (token->type != EXECUTABLE)
	{
		*tk = (*tk)->next;
		token = (*tk)->content;
	}
	if (fill_exec(token, &tree))
		return (EXIT_FAILURE);
	*tk = (*tk)->next;
	if (*tk)
		token = (*tk)->content;
	fill_arg(tree, tk_begin);
	token = tk_begin->content;
	fill_redirect(&tree, &tk_begin);
	while (token->type != SEPARATOR && *tk)
	{
		token = (*tk)->content;
		(*tk) = (*tk)->next;
	}
	return (EXIT_SUCCESS);
}
