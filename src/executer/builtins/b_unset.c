#include "minishell.h"

int	ft_strlen_sep(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

void	unset_var(t_shell *sh, t_tree *root)
{
	char	**var;
	int		i;
	int		j;

	root = root->branches->content;
	var = (char **)(root->content);
	i = 0;
	while (i < root->size)
	{
		j = 0;
		while (j < sh->size_env)
		{
			if (sh->env[j] && !ft_strncmp(sh->env[j], var[i], ft_strlen_sep(sh->env[j], '=')))
				sh->env[j] = NULL;
			j++;
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
