#include "minishell.h"

void	unset_var(t_shell *sh, t_tree *root)
{
	char	**var;
	int		i;
	t_list	*tmp;
	t_list	*before;

	root = root->branches->content;
	var = (char **)(root->content);
	before = NULL;
	i = -1;
	while (++i < root->size)
	{
		tmp = sh->env;
		while (tmp)
		{
			if (!ft_strncmpsep(var[i], tmp->content, ft_strlen(var[i]), '='))
			{
				before->next = tmp->next;
				ft_lstdelone(tmp, free);
			}
			else
				before = tmp;
			tmp = before->next;
		}
	}
}

int	b_unset(void *sh, t_tree *root)
{
	t_shell	*shell;
	t_tree	*tmp;

	shell = sh;
	tmp = ft_tr_leftchild(root);
	if (tmp)
	{
		tmp = tmp->content;
		if (tmp->type != ARGUMENT)
			return (EXIT_SUCCESS);
		unset_var(shell, root);
	}
	return (0);
}
