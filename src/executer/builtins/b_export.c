#include "minishell.h"

int	ft_verif_var_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i != 0)
			return (1);
		i++;
	}
	return (0);
}

int	b_export(void *sh, t_tree *root)
{
	t_shell	*shell;
	char	**tableau;
	int		i;
	char	*content;

	shell = sh;
	root = root->branches->content;
	tableau = root->content;
	i = 0;
	while (i < root->size)
	{
		if (ft_verif_var_env(tableau[i]))
		{
			content = malloc(sizeof(char) * (ft_strlen(tableau[i]) + 1));
			content = ft_strncpy(content, tableau[i], ft_strlen(tableau[i]));
			ft_lstadd_back(&shell->env, ft_lstnew(content));
		}
		i++;
	}
	return (0);
}
