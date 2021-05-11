#include "minishell.h"

void	unset_var(t_shell *sh, t_tree *root)
{
	char	**var;
	int		i;
	t_list	*tmp;
	t_list	*before;

	root = root->branches->content;
	var = (char **)(root->content);
	i = 0;
	while (i < root->size)
	{
		tmp = sh->env;
		while (tmp)
		{
			if (!ft_strncmpsep(var[i], tmp->content, ft_strlen(var[i]), '='))
			{
				tmp->content = NULL;
				before->next = tmp->next;
			}
			else
				before = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

int	b_unset(void *sh, t_tree *root)
{
	t_shell	*shell;

	shell = sh;
	if (root->branches)
		unset_var(shell, root);
	return (0);
}
