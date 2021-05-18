#include "minishell.h"

void	fill_tab(t_list *tk, char **arg, int *i)
{
	t_token	*token;

	*i = 0;
	token = tk->content;
	while (tk && token->type != SEPARATOR)
	{
		token = tk->content;
		if (token->type == ARGUMENT)
		{
			arg[*i] = malloc(sizeof(char) * (ft_strlen(token->value) + 1));
			ft_strncpy(arg[*i], token->value, ft_strlen(token->value));
			(*i)++;
		}
		tk = tk->next;
	}
	arg[*i] = NULL;
}

int	fill_arg(t_tree *tree, t_list *tk)
{
	char	**arg;
	int		nb_arg;
	int		i;

	nb_arg = ft_nb_arg(tk);
	if (nb_arg)
	{
		arg = malloc(sizeof(char *) * (nb_arg + 1));
		if (arg == NULL)
			return (MALLOC_BREAK);
		fill_tab(tk, arg, &i);
		ft_tr_addleft(tree, ft_tr_new(arg, ARGUMENT, i));
	}
	return (1);
}
