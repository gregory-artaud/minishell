#include "minishell.h"

int	ft_strncmpsep(char *s1, char *s2, unsigned int n, char sep)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != sep) && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] != sep)
		return (-1);
	return (0);
}

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
