#include "minishell.h"

void	unset_var(t_shell *sh, t_tree *root)
{
	char	**var;
	int		i;
	t_list	*tmp;
	t_list	*before;

	root = root->branches->content;
	var = (char **)(root->content);
	i = -1;
	while (++i < root->size)
	{
		tmp = sh->env;
		while (tmp)
		{
			if (!ft_strncmpsep(var[i], tmp->content, ft_strlen(var[i]), '='))
			{
				free(tmp->content);
				tmp->content = NULL;
				before->next = tmp->next;
				free(tmp);
			}
			else
				before = tmp;
			tmp = tmp->next;
		}
	}
}

int	b_unset(void *sh, t_tree *root)
{
	t_shell	*shell;
	t_tree	*tmp;

	shell = sh;
	if (root->branches)
	{
		tmp = root->branches->content;
		if (tmp->type == REDIRECT)
			create_file_redirect(tmp);
		else if (root->branches->next)
		{
			unset_var(shell, root);
			create_file_redirect(tmp);
		}
		else
			unset_var(shell, root);
	}
	return (0);
}
